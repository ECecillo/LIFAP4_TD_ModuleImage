#!/usr/bin/python3
import os
import sys
from sys import platform
import tarfile
import subprocess
import glob

###          OPTION D'EVALUATION       ###
MODES = ["FULLAUTO", "SEMIAUTO"]
MODE = "FULLAUTO"
# MODE = "SEMIAUTO"

# VERBOSE = True
VERBOSE = False


###          FONCTIONNALITES           ###
def msg(pb, penalite):
    global NOTE
    global RETOUR
    txt = "PROBLEME : " + pb + ". J'enleve " + str(penalite) + " points."
    print(txt)
    NOTE = NOTE - penalite
    RETOUR = RETOUR + "\n" + txt
    if NOTE < 0:
        print("Note < 0 ===> pas la peine d'aller plus loin ...")
        sys.exit(0)


def isdir(thefile):
    return os.path.isdir(thefile)


def isfile(thefile):
    return os.path.isfile(thefile)


def rmfiles(thedir):
    if isdir(thedir):
        files = glob.glob(thedir + "/*")
        for f in files:
            rmfiles(f)
        os.rmdir(thedir)
    else:
        if isfile(thedir):
            os.remove(thedir)


def filesize(read, enco="utf-8"):
    if read != "":
        fs = open(read, 'r', encoding=enco)
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


###           EXECUTION DU SCRIPT          ###

###  INIT  ###
os.system('clear')
NOTE = 5
RETOUR = ""

###  VERIFICATION OS = LINUX  ###
if VERBOSE:
    print("Python version = " + sys.version)
    print("Plateforme = " + platform)
if platform != "linux" and platform != "linux2":
    print("ERREUR : vous devez executer ce script sous Linux !")
    sys.exit(0)
elif VERBOSE:
    print("Verification Linux OK")

###  VERIFICATION PARAMETRE DU SCRIPT = NOM ARCHIVE  ###
if len(sys.argv) != 2:
    print("ERREUR : lancez le script avec l'archive en parametre: " + sys.argv[0] + " NUM_ETU1_NUM_ETU2.tgz")
    sys.exit(0)

FILENAME = sys.argv[1]
NOM_ARCHIVE = FILENAME.split(".")[0]
NUMEROS_ETU = NOM_ARCHIVE.split("_")
if VERBOSE:
    print("FILENAME = " + FILENAME)
    print("NOM_ARCHIVE = " + NOM_ARCHIVE)
    print("Numeros des etudiants =", end=' ')
    print(*NUMEROS_ETU, sep=' , ')
    print("===> note initiale = " + str(NOTE))

###  EXTRACTION DE L'ARCHIVE  ###
print("===> decompression de l'archive ...")
tar = tarfile.open(FILENAME)
DIR = tar.members[0].name.split("/")[0]
if VERBOSE:
    print("Repertoire principal = " + DIR)
if DIR != NOM_ARCHIVE:
    msg("Nom de l'archive et du repertoire principal different", 0.25)
tar.extractall()
tar.close()
print("===> decompression de l'archive ... done")

###  VERIFICATION DE L'ARBORESCENCE  ###
print("===> verification de l'arborescence ...")
if not isdir(DIR):
    msg("Repertoire principal inexistant", 5)
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
    print(make_process.stdout.decode("utf-8"))
    print("stderr:")
    print(make_process.stderr.decode("utf-8"))

if isfile("bin/exemple"):
    msg("make clean ne supprime pas bin/exemple", 0.1)
if isfile("bin/test"):
    msg("make clean ne supprime pas bin/test", 0.1)
if isfile("bin/affichage"):
    msg("make clean ne supprime pas bin/affichage", 0.1)

if len(glob.glob("obj/*.o")) != 0 or len(glob.glob("*.o")) != 0:
    msg("make clean ne supprime pas les fichiers objets", 0.5)
    print("Fichiers objets non supprimes:", end=' ')
    print(*glob.glob("obj/*.o"), sep=' , ')
    print(*glob.glob("*.o"), sep=' , ')

print("===> make clean  ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

###  COMPILATION  ###
print("===> make ...")
make_process = subprocess.run(['make'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

warning = str(make_process.stderr).count("warning:")
if VERBOSE:
    print("stdout:")
    print(make_process.stdout.decode("utf-8"))
    print("stderr:")
    print(make_process.stderr.decode("utf-8"))
if warning > 0:
    msg("Il a " + str(warning) + " warnings a la compilation", min(warning * 0.1, 0.5))
elif VERBOSE:
    print("Pas de warning a la compilation")

error = str(make_process.stderr).count("error:")
if error > 0:
    msg("Il a " + str(error) + " erreurs a la compilation!", 1)
elif VERBOSE:
    print("Pas d'erreur a la compilation")

if len(glob.glob("obj/*.o")) != 5:
    print("Attention : mauvais nombre de fichiers objets")
if len(glob.glob("*.o")) != 0 or len(glob.glob("src/*.o")) != 0:
    msg("Fichiers objets dans le mauvais repertoire", 0.5)

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

make_process = subprocess.run(['bin/exemple'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
if VERBOSE:
    print("stdout:")
    print(make_process.stdout.decode("utf-8"))
    print("stderr:")
    print(make_process.stderr.decode("utf-8"))

if not isfile("data/image1.ppm"):
    msg("image1.ppm non generee (ou pas dans data)", 0.5)
elif isfile("../image1.ppm"):
    im_file_etu = open("data/image1.ppm", 'r')
    image_etu = im_file_etu.read()
    im_file_prof = open("../image1.ppm", 'r')
    image_prof = im_file_prof.read()
    if image_etu != image_prof:
        msg("image1.ppm erronee", 0.5)
    elif VERBOSE:
        print("image1.ppm OK")
    im_file_prof.close()
    im_file_etu.close()
else:
    make_process = subprocess.run(['eog', 'data/image1.ppm'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    ok = input('image1 ok (o/n) ? ')
    if ok == 'n':
        msg("image1.ppm erronee", 0.5)

if not isfile("data/image2.ppm"):
    msg("image2.ppm non generee  (ou pas dans data)", 0.5)
elif isfile("../image2.ppm"):
    im_file_etu = open("data/image2.ppm", 'r')
    image_etu = im_file_etu.read()
    im_file_prof = open("../image2.ppm", 'r')
    image_prof = im_file_prof.read()
    if image_etu != image_prof:
        msg("image2.ppm erronee", 0.5)
    elif VERBOSE:
        print("image2.ppm OK")
    im_file_prof.close()
    im_file_etu.close()
else:
    make_process = subprocess.run(['eog', 'data/image2.ppm'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
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
        print(make_process.stdout.decode("utf-8"))
        print("stderr:")
        print(make_process.stderr.decode("utf-8"))

if isfile("../mainTestRegression.cpp"):
    if VERBOSE:
        print("Test de regression ...")
    replaceInFile('src/Image.h', 'src/ImageRegression.h', 'private', 'public')
    subprocess.run(['cp', '../mainTestRegression.cpp', 'src/mainTestRegression.cpp'])
    subprocess.run(
        ['g++', '-ggdb', '-c', 'src/mainTestRegression.cpp', '-I/usr/include/SDL2', '-o', 'obj/mainTestRegression.o'])
    subprocess.run(['g++', '-ggdb', '-c', 'src/Image.cpp', '-I/usr/include/SDL2', '-o', 'obj/Image.o'])
    subprocess.run(
        ['g++', '-ggdb', '-o', 'bin/testRegression', 'obj/mainTestRegression.o', 'obj/Image.o', 'obj/Pixel.o', '-lSDL2',
         '-lSDL2_ttf', '-lSDL2_image'])
    make_process = subprocess.run(['bin/testRegression'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if VERBOSE:
        print("stdout:")
        print(make_process.stdout.decode("utf-8"))
        print("stderr:")
        print(make_process.stderr.decode("utf-8"))
    errors = make_process.stdout.decode("utf-8")
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
    make_process = subprocess.run(['valgrind','--tool=memcheck','--leak-check=summary','bin/test'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if VERBOSE:
        print("stdout:")
        print(make_process.stdout.decode("utf-8"))
        print("stderr:")
        print(make_process.stderr.decode("utf-8"))
    str_stderr = make_process.stderr.decode("utf-8")
    istart = int(str_stderr.find("definitely lost: "))
    iend = int(str_stderr.find("bytes", istart))
	nb_bytes_lost = 0
    if istart==-1 and iend==-1:
        if str_stderr.find("All heap blocks were fread")!=-1:
            msg("Fuite memoire sur la pile", 0.5)
    else:
        nb_bytes_lost = int(str_stderr[istart + 17:iend])
    if VERBOSE:
        print("Nombre de bytes perdus : " + str(nb_bytes_lost))
    if nb_bytes_lost > 0:
        msg("Il a " + str(nb_bytes_lost) + " octets perdus", min(nb_bytes_lost * 0.01, 0.5))
    elif VERBOSE:
        print("Aucune fuite memoire")

    nb_invalid_write = str_stderr.count("Invalid write")
    if VERBOSE:
        print("Nombre d'acces invalides : " + str(nb_invalid_write))
    if nb_invalid_write > 0:
        msg("Il a " + str(nb_invalid_write) + " acces invalides a la memoire", min(nb_invalid_write * 0.1, 0.5))
    elif VERBOSE:
        print("Aucun acces invalide")

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
            print(make_process.stdout.decode("utf-8"))
            print("stderr:")
            print(make_process.stderr.decode("utf-8"))
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
readmes = ["readme.txt", "Readme.txt", "README.txt"]
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
    if not isfile("doc/html/class_image.html"):
        msg("Doxygen n'a pas genere de doc pour la classe Image", 0.5)
    else:
        sz = filesize("doc/html/class_image.html", 'latin-1')
        if VERBOSE:
            print("taille de la page de la classe Image : " + str(sz) + " octets")
        if sz < 15000:
            msg("Documentation de la classe Image insuffisante", 0.25)
    if not isfile("doc/html/class_pixel.html"):
        msg("Doxygen n'a pas genere de doc pour la classe Pixel", 0.5)
    else:
        sz = filesize("doc/html/class_pixel.html", 'latin-1')
        if VERBOSE:
            print("taille de la page de la classe Pixel : " + str(sz) + " octets")
        if sz < 10000:
            msg("Documentation de la classe Pixel insuffisante", 0.25)
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
    msg("Pas assez de fonctions commentees", 0.5)
if n_param < 15:
    msg("Pas assez de parametres commentees", 0.5)

print("===> documentation ... done")
if VERBOSE:
    print("==> note = " + str(NOTE))

###  ASSERTIONS  ###
print("===> assert ...")
search = ["assert","throw"]
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
            if texte.count("unsigned char") == 0:
                msg("Mauvais type des donnees membres de Pixel", 0.25)
            fi.close()
    ## Image.h ##
    files = ["src/Image.h", "src/image.h"]
    for f in files:
        if isfile(f):
            fi = open(f, 'r', encoding="latin-1")
            texte = fi.read()

            if texte.count("include") > 4:
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
