#!/usr/bin/python3
import os
import shutil
import sys
from sys import platform
import tarfile
import subprocess
import glob
import re

###          OPTION D'EVALUATION       ###
MODES = ["FULLAUTO", "SEMIAUTO"]
MODE = "FULLAUTO"
# MODE = "SEMIAUTO"

VERBOSE = True
# VERBOSE = False

###          FONCTIONNALITES           ###
def msg(pb, penalite):
    global NOTE
    global RETOUR
    txt = "PROBLEME : " + pb + ". J'enleve " + str(penalite) + " points."
    print(txt)
    if NOTE > 0:
        NOTE = max(round(NOTE - penalite, 2), 0)
    RETOUR = RETOUR + "\n" + txt


def isdir(thefile):
    return os.path.isdir(thefile)


def isfile(thefile):
    return os.path.isfile(thefile)


def listfiles(a):
    if isdir(a):
        l = []
        files = glob.glob(a + "/*")
        for f in files:
            l.extend(listfiles(f))
        return l
    elif isfile(a):
        nom_complet = a.split("/")[-1]
        chemin = "/".join(a.split("/")[0:-1])
        nom = nom_complet.split(".")[0]
        if "." in nom_complet:
            ext = ".".join(nom_complet.split(".")[1:])
        else:
            ext = ""
        return [{"f": a, "nom": nom, "ext": ext, "nc": nom_complet, "ch": chemin}]
    else:
        return []


def rmfiles(thedir):
    if isdir(thedir):
        #files = glob.glob(thedir + "/*")
        #for f in files:
        #    rmfiles(f)
        #os.rmdir(thedir)
        shutil.rmtree(thedir, ignore_errors=True) #fonctionne meme s'il y a des fichiers caches
    else:
        if isfile(thedir):
            os.remove(thedir)


def filesize(read, enco="utf-8"):
    if read != "":
        en = enco
        # en = "latin1"
        try:
            fs = open(read, 'r', encoding=en)
            texte = fs.read()
        except UnicodeDecodeError:
            en = "latin1"
        except Error as exc_ret:
            print(exc_ret)
            sys.exit(-1)
        finally:
            fs.close()
        fs = open(read, 'r', encoding=en)
        texte = fs.read()
        longueur = len(texte)
        fs.close()
        return longueur
    else:
        return 0


def filein(lst):
    read = ""
    for rm in lst:
        if isfile(rm):
            read = rm
    return read


def countInFile(f, word):
    if isfile(f):
        with open(f, 'r', errors='ignore') as fs:
            texte = fs.read()
            n = texte.count(word)
            fs.close()
        return n
    else:
        return 0


def replaceInFile(fin, fout, wordin, wordout):
    if isfile(fin):
        texte = ''
        with open(fin, 'r', errors='ignore') as fs:
            texte = fs.read()
            texte = texte.replace(wordin, wordout)
            fs.close()
        with open(fout, 'w', errors='ignore') as fs:
            fs.write(texte)
            fs.close()


def isFiledatesOk(filedates, filemodif):
    ok = True
    for f, lm in filedates.items():
        if isfile(f):
            lastModif = os.stat(f).st_mtime_ns
            changed = lastModif != lm
            filedates[f] = lastModif
            if f in filemodif:
                ok = ok and (filemodif[f] == changed)
    return ok


def isDepOk(f, filedates, filemodif):
    global VERBOSE
    if isfile(f):
        os.utime(f)
    make_process = subprocess.run(['make'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    ok = isFiledatesOk(filedates, filemodif)
    if VERBOSE:
        print('Modif de ' + f + ', recompilation ' + {True: 'ok', False: 'pas ok'}[ok])
        print("stdout:")
        print(make_process.stdout.decode("utf-8", "ignore"))
    return ok


###           EXECUTION DU SCRIPT          ###

###  INIT  ###
os.system('clear')
print("\n\n--------------------EXECUTION DU SCRIPT-----------------------")
print("--------------------------------------------------------------\n\n")
NOTE = 5
RETOUR = ""

###  VERIFICATION OS LINUX + VERSION PYTHON ###
if platform != "linux" and platform != "linux2":
    print("ERREUR : vous devez executer ce script sous Linux !")
    sys.exit(0)
elif VERBOSE:
    print("Plateforme = " + platform)
    print("Verification Linux OK")

version = sys.version_info
if version[0] != 3 or (version[0] == 3 and version[1] < 5):  # minimum 3.5 pour subprocess.run() et glob recursif
    print("ERREUR : vous devez executer ce script avec Python 3 (3.5 minimum) !")
    sys.exit(0)
elif VERBOSE:
    print("Python version = " + sys.version)
    print("Verification Python 3.5 minimum OK")

###  VERIFICATION PARAMETRE DU SCRIPT = NOM ARCHIVE  ###
if len(sys.argv) != 2:
    print("ERREUR : lancez le script avec l'archive en parametre: " + sys.argv[0] + " NUM_ETU1_NUM_ETU2.tgz")
    sys.exit(0)

### IDENTIFICATION DES ETUDIANTS ET NOM D'ARCHIVE - PRISE EN COMPTE QUE L'ARCHIVE PEUT PROVENIR DE TOMUSS ###
FILENAME = sys.argv[1]
if VERBOSE:
    print("FILENAME = " + FILENAME)
    print("===> note initiale = " + str(NOTE))
NUMEROS_ETU = []
NOM_ARCHIVE_ATTENDU = ""
for mot in FILENAME.replace("p", "1").split(".")[0].split("_"):
    if mot.isdigit() and len(mot) == 8:
        NUMEROS_ETU.append(mot)
        if len(NUMEROS_ETU) > 1:
            NOM_ARCHIVE_ATTENDU += "_"
        NOM_ARCHIVE_ATTENDU += mot
for mot in FILENAME.replace("P", "1").split(".")[0].split("_"):
    if mot.isdigit() and len(mot) == 8:
        NUMEROS_ETU.append(mot)
        if len(NUMEROS_ETU) > 1:
            NOM_ARCHIVE_ATTENDU += "_"
        NOM_ARCHIVE_ATTENDU += mot
if len(NUMEROS_ETU) == 0:
    print("ERREUR : aucun numero d'etudiant detecte dans: " + FILENAME)
    sys.exit(0)
if not FILENAME.replace("p", "1").split(".")[0].endswith(NOM_ARCHIVE_ATTENDU) and not \
FILENAME.replace("P", "1").split(".")[0].endswith(NOM_ARCHIVE_ATTENDU):
    msg("L'archive  " + FILENAME + "  ne suit pas le format NUM_ETU1_NUM_ETU2_NUM_ETU3.tgz", 0.5)
f = FILENAME
if "#" in f:
    f = f.split("#")[1]
NOM_ARCHIVE = f[f.find(NUMEROS_ETU[0][1:]) - 1] + NUMEROS_ETU[0][1:] + f.split(".")[0].split(NUMEROS_ETU[0][1:])[1]
if VERBOSE:
    print("NOM_ARCHIVE = " + NOM_ARCHIVE)
    print("Numeros des etudiants =", end=' ')
    print(*NUMEROS_ETU, sep=', ')

###  EXTRACTION DE L'ARCHIVE  ###
print("===> decompression de l'archive ...")
tar = tarfile.open(FILENAME)
#DIR = tar.members[0].name.split("/")[0]
DIR = None
for tarmember in tar:
    if tarmember.isdir() and '/' not in tarmember.name:
        DIR = tarmember.name
if DIR is None:
    print("Aucun dossier a la racine de l'archive")
    sys.exit(0)
if VERBOSE:
    print("Repertoire principal = " + DIR)
if DIR != NOM_ARCHIVE:
    msg("Nom de l'archive et du repertoire principal different", 0.25)
tar.extractall()
tar.close()
print("===> decompression de l'archive ... done")

###  VERIFICATION DE L'ARBORESCENCE  ###
print("===> verification de l'arborescence ...")
if not isdir(DIR) or DIR == ".":
    print("ERREUR : Repertoire principal inexistant")
    sys.exit(0)
os.chdir(os.getcwd() + "/" + DIR)
if not isdir("bin"):
    msg("Dossier bin inexistant", 0.5)
if not isdir("src"):
    msg("Dossier src inexistant", 0.5)
if not isdir("doc"):
    msg("Dossier doc inexistant", 0.5)
if not isdir("data"):
    msg("Dossier data inexistant", 0.5)
print("===> verification de l'arborescence ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

### VERIFICATION DES FICHIERS PRESENTS/ABSENTS ###
FICHIERSIND = {  # Fichiers attendus et indispensables
    "Pixel.h": {"nom": "Pixel", "ext": "h", "loc": "src"},
    "Pixel.cpp": {"nom": "Pixel", "ext": "cpp", "loc": "src"},
    "Image.h": {"nom": "Image", "ext": "h", "loc": "src"},
    "Image.cpp": {"nom": "Image", "ext": "cpp", "loc": "src"},
    "mainTest.cpp": {"nom": "mainTest", "ext": "cpp", "loc": "src"}
}
FICHIERSNONIND = {
    # Fichiers attendus mais non indispensables (fichiers generes ou dont l'absence est traitee plus loin)
    "mainExemple.cpp": {"nom": "mainExemple", "ext": "cpp", "loc": "src"},
    "mainAffichage.cpp": {"nom": "mainAffichage", "ext": "cpp", "loc": "src"},
    "test": {"nom": "test", "ext": "", "loc": "bin"},
    "exemple": {"nom": "exemple", "ext": "", "loc": "bin"},
    "affichage": {"nom": "affichage", "ext": "", "loc": "bin"},
    "image1.ppm": {"nom": "image1", "ext": "ppm", "loc": "data"},
    "image2.ppm": {"nom": "image2", "ext": "ppm", "loc": "data"},
    "image.doxy": {"nom": "image", "ext": "doxy", "loc": "doc"},
    "testRegression": {"nom": "testRegression", "ext": "", "loc": "bin"},
    "mainTestRegression.cpp": {"nom": "mainTestRegression", "ext": "cpp", "loc": "src"},
    "ImageRegression.h": {"nom": "ImageRegression", "ext": "h", "loc": "src"}
}
FICHIERSPRESENTS = listfiles(".")
for nc, prop in FICHIERSIND.items():
    present = False
    for f in FICHIERSPRESENTS:
        if f["nc"] == nc:
            present = True
    if not present:
        msg(
            "Au minimum, tous les fichiers Pixel.h, Pixel.cpp, Image.h, Image.cpp et mainTest.cpp doivent etre presents",
            5)
        break
doclatex = False
for f in FICHIERSPRESENTS:
    if "/html" in f["ch"]:
        continue
    if "/latex" in f["ch"]:
        doclatex = True
        continue
    if "dll" in f["ext"].lower() or "mingw" in f["f"].lower():
        continue
    if "sdl" in f["f"].lower():
        continue
    if f["ext"] in ["cbp", "layout"]:
        continue
    if f["ext"] in ["o", "depend", "d"]:
        continue
    if f["nc"] in ["documentation.h"]:
        continue
    if f["ext"] in ["ttf", "woff", "wav", "mp3"]:
        continue
    if f["ext"] in ["supp"]:
        continue
    if f["nom"].lower() == "makefile":
        continue
    if f["nom"].lower() == "readme":
        continue
    if f["nc"] in FICHIERSIND:
        continue
    if f["nc"] in FICHIERSNONIND:
        continue
    if "dia" == f["ext"] or "xmi" == f["ext"] or (
                ("png" == f["ext"].lower() or "jpg" == f["ext"].lower()) and "diagramme" in f["nom"].lower()):
        if not "doc" in f["ch"]:
            msg("Le diagramme des classes " + f["nc"] + " doit etre dans le dossier doc/", 0.1)
        continue
    msg("Le fichier " + f["nc"] + " ne doit pas etre la", 0.1)
if doclatex:
    msg("La documentation n'est pas demandee en latex", 0.1)
print("===> verification des fichiers presents... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

###  VERIFICATION MAKEFILE  ###
print("===> verification Makefile ...")
MAKEFILE = "Makefile"
if not isfile(MAKEFILE):
    MAKEFILE = "makefile"
    if not isfile(MAKEFILE):
        MAKEFILE = "???"
        msg("Makefile introuvable", 2)
if VERBOSE:
    print("Makefile = " + MAKEFILE)
    print("==> note = " + str(NOTE))
print("===> verification Makefile ... done")

###  CLEAN  ###
print("===> make clean ...")
if isfile(MAKEFILE):
    file_makefile = open(MAKEFILE, 'r')
    texte = file_makefile.read()
    if texte.find("clean:") == -1 and texte.find("clean :") == -1:
        msg("Makefile ne contient pas la cible clean", 0.25)
    file_makefile.close()

make_process = subprocess.run(['make', 'clean'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
if VERBOSE:
    print("stdout:")
    print(make_process.stdout.decode("utf-8", "ignore"))
    print("stderr:")
    print(make_process.stderr.decode("utf-8", "ignore"))

if isfile("bin/exemple") or isfile("./exemple"):
    msg("make clean ne supprime pas l'executable exemple", 0.1)
if isfile("bin/test") or isfile("./test"):
    msg("make clean ne supprime pas l'executable test", 0.1)
if isfile("bin/affichage") or isfile("./affichage"):
    msg("make clean ne supprime pas l'executable affichage", 0.1)

# if len(glob.glob("obj/*.o")) != 0 or len(glob.glob("*.o")) != 0:
if len(glob.glob("**/*.o", recursive=True)) != 0:
    msg("make clean ne supprime pas les fichiers objets", 0.5)
    print("Fichiers objets non supprimes:", end=' ')
    print(*glob.glob("**/*.o", recursive=True), sep=' , ')

for f in glob.glob("**/*.o", recursive=True):
    os.remove(f)
for f in glob.glob('./exemple') + glob.glob('bin/exemple') + glob.glob('./test') + glob.glob('bin/test') + glob.glob(
        './affichage') + glob.glob('bin/affichage'):
    os.remove(f)

print("===> make clean  ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

###  COMPILATION  ###
print("===> make ...")
make_process = subprocess.run(['make'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

warning = str(make_process.stderr).count("warning:")
if VERBOSE:
    print("stdout:")
    print(make_process.stdout.decode("utf-8", "ignore"))
    print("stderr:")
    print(make_process.stderr.decode("utf-8", "ignore"))
if warning > 0:
    msg("Il y a " + str(warning) + " warnings a la compilation", min(warning * 0.1, 0.5))
elif VERBOSE:
    print("Pas de warning a la compilation")

error = str(make_process.stderr).count("error:")
if error > 0:
    msg("Il y a " + str(error) + " erreurs a la compilation!", 1)
elif VERBOSE:
    print("Pas d'erreur a la compilation")

if len(glob.glob("**/*.o", recursive=True)) != 5:
    print("Attention : mauvais nombre de fichiers objets")
if len(glob.glob("obj/*.o")) != len(glob.glob("**/*.o", recursive=True)):
    msg("Fichiers objets dans le mauvais repertoire", 0.5)

makedepok = True
filedates = {'obj/mainTest.o': 0, 'obj/Pixel.o': 0, 'obj/Image.o': 0, 'bin/test': 0}
isFiledatesOk(filedates, {})
makedepok = isDepOk('src/mainTest.cpp', filedates, {'obj/mainTest.o': True, 'obj/Pixel.o': False, 'obj/Image.o': False,
                                                    'bin/test': True}) and makedepok
makedepok = isDepOk('src/Image.cpp', filedates, {'obj/mainTest.o': False, 'obj/Pixel.o': False, 'obj/Image.o': True,
                                                 'bin/test': True}) and makedepok
makedepok = isDepOk('src/Image.h', filedates,
                    {'obj/mainTest.o': True, 'obj/Pixel.o': False, 'obj/Image.o': True, 'bin/test': True}) and makedepok
makedepok = isDepOk('src/Pixel.cpp', filedates, {'obj/mainTest.o': False, 'obj/Pixel.o': True, 'obj/Image.o': False,
                                                 'bin/test': True}) and makedepok
makedepok = (isDepOk('src/Pixel.h', filedates,
                    {'obj/mainTest.o': True, 'obj/Pixel.o': True, 'obj/Image.o': True, 'bin/test': True}) or
            isDepOk('src/Pixel.h', filedates,
                    {'obj/mainTest.o': False, 'obj/Pixel.o': True, 'obj/Image.o': True, 'bin/test': True})) and makedepok
makedepok = isDepOk('aucun_fichier', filedates, {'obj/mainTest.o': False, 'obj/Pixel.o': False, 'obj/Image.o': False,
                                                 'bin/test': False}) and makedepok
if not makedepok:
    msg('Les dependances ne sont pas correctement prises en compte dans le Makefile', 0.25)

if VERBOSE:
    print("==> note = " + str(NOTE))
print("===> make ... done")

###  EXECUTION EXE  ###
## EXEMPLE ##
print("===> bin/exemple ...")

if not isfile("bin/exemple"):
    msg("make ne genere pas bin/exemple", 0.5)
if VERBOSE and isfile("data/image1.ppm"):
    print("image1.ppm existe, suppression")
    os.remove("data/image1.ppm")
if VERBOSE and isfile("data/image2.ppm"):
    print("image2.ppm existe, suppression")
    os.remove("data/image2.ppm")

if isfile("bin/exemple"):
    make_process = subprocess.run(['bin/exemple'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if VERBOSE:
        print("stdout:")
        print(make_process.stdout.decode("utf-8", "ignore"))
        print("stderr:")
        print(make_process.stderr.decode("utf-8", "ignore"))

if not isfile("data/image1.ppm"):
    msg("image1.ppm non generee (ou pas dans data)", 0.5)
elif isfile("../image1.ppm"):
    im_file_etu = open("data/image1.ppm", 'r')
    image_etu = im_file_etu.read()
    im_file_prof = open("../image1.ppm", 'r')
    image_prof = im_file_prof.read()
    if image_etu != image_prof:
        msg("image1.ppm erronee", 0.25)
    elif VERBOSE:
        print("image1.ppm OK")
    im_file_prof.close()
    im_file_etu.close()
else:
    make_process = subprocess.run(['display', 'data/image1.ppm'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    ok = input('image1 ok (o/n) ? ')
    if ok == 'n':
        msg("image1.ppm erronee", 0.5)

if not isfile("data/image2.ppm"):
    msg("image2.ppm non generee (ou pas dans data)", 0.5)
elif isfile("../image2.ppm"):
    im_file_etu = open("data/image2.ppm", 'r')
    image_etu = im_file_etu.read()
    im_file_prof = open("../image2.ppm", 'r')
    image_prof = im_file_prof.read()
    if image_etu != image_prof:
        msg("image2.ppm erronee", 0.25)
    elif VERBOSE:
        print("image2.ppm OK")
    im_file_prof.close()
    im_file_etu.close()
else:
    make_process = subprocess.run(['display', 'data/image2.ppm'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    ok = input('image2 ok (o/n) ? ')
    if ok == 'n':
        msg("image2.ppm erronee", 0.5)

print("===> bin/exemple ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

## test ##
print("===> bin/test ...")
if not isfile("bin/test"):
    msg("make ne genere pas bin/test", 0.5)
else:
    make_process = subprocess.run(['bin/test'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if VERBOSE:
        print("stdout:")
        print(make_process.stdout.decode("utf-8", "ignore"))
        print("stderr:")
        print(make_process.stderr.decode("utf-8", "ignore"))

if isfile("../mainTestRegression.cpp"):
    if VERBOSE:
        print("Test de regression ...")
    replaceInFile('src/Image.h', 'src/ImageRegression.h', 'private', 'public')
    subprocess.run(['cp', '../mainTestRegression.cpp', 'src/mainTestRegression.cpp'])
    subprocess.run(
        ['g++', '-ggdb', '-std=c++11', '-c', 'src/mainTestRegression.cpp', '-I/usr/include/SDL2', '-o',
         'obj/mainTestRegression.o'])
    subprocess.run(['g++', '-ggdb', '-std=c++11', '-c', 'src/Image.cpp', '-I/usr/include/SDL2', '-o', 'obj/Image.o'])
    subprocess.run(
        ['g++', '-ggdb', '-std=c++11', '-o', 'bin/testRegression', 'obj/mainTestRegression.o', 'obj/Image.o',
         'obj/Pixel.o', '-lSDL2',
         '-lSDL2_ttf', '-lSDL2_image'])
    if not isfile("bin/testRegression"):
        msg("Le test de regression prof ne peut pas compiler (voir ci-dessus les erreurs de compilation)", 0.5)
    else:
        make_process = subprocess.run(['bin/testRegression'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if VERBOSE:
            print("stdout:")
            print(make_process.stdout.decode("utf-8", "ignore"))
            print("stderr:")
            print(make_process.stderr.decode("utf-8", "ignore"))
        errors = make_process.stdout.decode("utf-8", "ignore")
        nb_errors = errors.count("ERREUR")
        if nb_errors > 0:
            msg("Il y a " + str(nb_errors) + " erreurs dans les tests de regression", min(nb_errors * 0.1, 0.5))
        if VERBOSE:
            print("Test de regression ... done")

print("===> bin/test ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

print("===> valgrind sur bin/test ...")
if isfile("bin/test"):
    make_process = subprocess.run(['valgrind', '--tool=memcheck', '--leak-check=summary', 'bin/test'],
                                  stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if VERBOSE:
        print("stdout:")
        print(make_process.stdout.decode("utf-8", "ignore"))
        print("stderr:")
        print(make_process.stderr.decode("utf-8", "ignore"))
    str_stderr = make_process.stderr.decode("utf-8", "ignore")
    istart = int(str_stderr.find("definitely lost: "))
    iend = int(str_stderr.find("bytes", istart))
    nb_bytes_lost = 0
    if istart == -1 and iend == -1:
        if str_stderr.find("All heap blocks were fread") != -1:
            msg("Fuite memoire sur la pile", 0.5)
    else:
        nb_bytes_lost = int(str_stderr[istart + 17:iend].replace(',', ''))
    if VERBOSE:
        print("Nombre de bytes perdus : " + str(nb_bytes_lost))
    if nb_bytes_lost > 0:
        msg("Il y a " + str(nb_bytes_lost) + " octets perdus", min(nb_bytes_lost * 0.01, 0.5))
    elif VERBOSE:
        print("Aucune fuite memoire")

    nb_invalid_write = str_stderr.count("Invalid write")
    nb_invalid_read = str_stderr.count("Invalid read")
    if VERBOSE:
        print("Nombre d'acces invalides : " + str(nb_invalid_write + nb_invalid_read))
    if nb_invalid_write > 0:
        msg("Il y a " + str(nb_invalid_write) + " acces invalides en ecriture a la memoire",
            min(nb_invalid_write * 0.1, 0.5))
    if nb_invalid_read > 0:
        msg("Il y a " + str(nb_invalid_read) + " acces invalides en lecture a la memoire",
            min(nb_invalid_read * 0.1, 0.5))

print("===> valgrind sur bin/test ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

## affichage ##
print("===> bin/affichage ...")
if not isfile("bin/affichage"):
    msg("make ne genere pas bin/affichage", 0.5)
else:
    if MODE == "SEMIAUTO":
        make_process = subprocess.run(['bin/affichage'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if VERBOSE:
            print("stdout:")
            print(make_process.stdout.decode("utf-8", "ignore"))
            print("stderr:")
            print(make_process.stderr.decode("utf-8", "ignore"))
        ok = input('affichage image ok (o/n) ? ')
        if ok == 'n':
            msg("bin/affichage non fonctionnel", 0.5)
        ok = input('zoom/dezoom ok (o/n) ? ')
        if ok == 'n':
            msg("zoom/dezoom non fonctionnel", 0.25)
            # TODO : else: automatiser la verif de bin/affichage

print("===> bin/affichage ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

###  README  ###
print("===> readme ...")
readmes = ["readme.txt", "Readme.txt", "README.txt", "readme.md", "Readme.md", "README.md"]
readme = filein(readmes)
if readme != "":
    longueur = filesize(readme)
    if VERBOSE:
        print("longueur du fichier " + readme + " : " + str(longueur) + " caracteres")
    if MODE == "SEMIAUTO":
        make_process = subprocess.run(['gedit', readme], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        ok = input('readme ok (o/n) ? ')
        if ok == 'n':
            msg("readme pas ok", 1)
    elif longueur < 500:
        msg(readme + " pas assez detaille", 0.5)
else:
    msg("readme introuvable", 1)

print("===> readme ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

###  DOCUMENTATION  ###
print("===> documentation ...")
doxys = ["doc/image.doxy", "doc/doxyfile"]
doxy = filein(doxys)
if doxy != "":
    rmfiles("doc/html")
    rmfiles("doc/latex")
    make_process = subprocess.run(['doxygen', doxy], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if not isfile("doc/html/index.html"):
        msg("Doxygen n'a pas genere doc/html/index.html, mauvais chemin dans OUTPUT_DIRECTORY et/ou INPUT?", 1)
    v1 = isfile("doc/html/class_image.html")
    v2 = isfile("doc/html/classImage.html")
    if not v1 and not v2:
        msg("Doxygen n'a pas genere de doc pour la classe Image", 0.25)
    v1 = isfile("doc/html/class_pixel.html")
    v2 = isfile("doc/html/classPixel.html")
    if not v1 and not v2:
        msg("Doxygen n'a pas genere de doc pour la classe Pixel", 0.25)
else:
    msg("doc/image.doxy introuvable", 1)

files_h = ["src/image.h", "src/Image.h", "src/pixel.h", "src/Pixel.h"]
n_brief = 0
n_param = 0
for f in files_h:
    n_brief += countInFile(f, "brief")
    n_param += countInFile(f, "param")
if VERBOSE:
    print("Nombre de fonctions commentees : " + str(n_brief))
    print("Nombre de parametres commentes : " + str(n_param))
if n_brief < 20:
    msg("Pas assez de fonctions commentees", 0.25)
if n_param < 15:
    msg("Pas assez de parametres commentees", 0.25)

print("===> documentation ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

###  ASSERTIONS  ###
print("===> assert ...")
search = ["assert(", "assert (", "throw"]
files = ["src/image.h", "src/Image.h", "src/pixel.h", "src/Pixel.h", "src/image.cpp", "src/Image.cpp", "src/pixel.cpp",
         "src/Pixel.cpp"]
n = 0
for f in files:
    for s in search:
        n += countInFile(f, s)
if VERBOSE:
    print("Nombre d'assertions : " + str(n))
if n < 10:
    msg("Pas assez d'assertions", 0.5)
print("===> assert ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

###  CODE  ###
print("===> code ...")
if MODE == "FULLAUTO":
    ## Pixel.h ##
    files = ["src/Pixel.h", "src/pixel.h"]
    for f in files:
        if isfile(f):
            fi = open(f, 'r', encoding="latin-1")
            texte = fi.read()
            texte = re.sub("(?<=\/\*)(.*?)(?=\*\/)", "", texte, 0, re.DOTALL)
            texte = re.sub("//.*", "", texte)
            if texte.count("unsigned char") == 0:
                msg("Mauvais type des donnees membres de Pixel", 0.25)
            fi.close()
    ## Image.h ##
    files = ["src/Image.h", "src/image.h"]
    for f in files:
        if isfile(f):
            fi = open(f, 'r', encoding="latin-1")
            texte = fi.read()
            texte = re.sub("(?<=\/\*)(.*?)(?=\*\/)", "", texte, 0, re.DOTALL)
            texte = re.sub("//.*", "", texte)

            if texte.count("#include") > 4:
                msg("Des include inutiles dans Image.h", 0.25)

            iend = texte.find("getPix")
            istart = texte[:iend].rfind("Pixel")
            if texte[istart:iend].find("*") != -1 or texte[istart:iend].find("&") == -1:
                msg("Mauvais type de retour de getPix", 0.5)

            nb_const_manquant = 0
            istart = texte.find("getPix")
            istart2 = texte[istart:].find(")")
            istart += istart2 + 1
            iend = texte[istart:].find(";")
            iend += istart
            if texte[istart:iend].find("const") == -1:
                nb_const_manquant += 1

            istart = texte.find("setPix")
            iend = texte[istart:].find(")")
            iend += istart
            istart = texte[istart:iend].rfind(",") + istart + 1
            if texte[istart:iend].find("const") == -1 or texte[istart:iend].find("&") == -1:
                nb_const_manquant += 1

            if nb_const_manquant > 0:
                msg("Manque des const", 0.5)

            if texte.find("dimx") == -1 or texte.find("dimy") == -1 or texte.find("tab") == -1:
                msg("Mauvais nom des donnees membres", 0.5)
            if texte.find("Image") == -1 or texte.find("getPix") == -1 or texte.find("setPix") == -1 or texte.find(
                    "dessinerRectangle") == -1 or texte.find("effacer") == -1:
                msg("Manque des fonctions ou mauvais noms", 0.5)
            if texte.find("sauver") == -1 or texte.find("ouvrir") == -1 or texte.find("afficher") == -1:
                msg("Manque les fonctions I/O", 0.5)

            fi.close()
else:
    command = ['gedit']
    command.extend(glob.glob("src/*.*"))
    make_process = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    points = min(int(input('nombre de points a deduire ? ')), 2)
    if points > 0:
        msg("Erreurs dans le code", points)

print("===> code ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

###  RESUME  ###
print("\nBILAN\n=====")
print(RETOUR)
print("Les etudiants ayant comme numeros : ", end='')
print(*NUMEROS_ETU, sep=' , ', end=' ')
print("ont la note " + str(NOTE) + "\n")
foutput = open('../' + NOM_ARCHIVE + '_feedback.txt', 'w')
foutput.write(NOM_ARCHIVE + " : " + str(NOTE) + "\n\n" + RETOUR)
foutput.close()
