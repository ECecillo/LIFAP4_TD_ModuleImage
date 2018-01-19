#!/usr/bin/python3
import re
import os
import sys
import tarfile
import subprocess
import shutil
import glob

os.system('clear')




def msg(pb, penalite):
	global NOTE
	global RETOUR
	txt = "@@@PROBLEME : "+pb+". J'enleve "+str(penalite)+" points"
	print(txt)
	NOTE = NOTE - penalite
	RETOUR = RETOUR + "\n " + txt 
	return NOTE
	return RETOUR
	if NOTE<0:
		print("Note < 0 ===> pas la peine d'aller plus loin ...")
		sys.exit(0)
	

def isdir(fi):
	return os.path.isdir(fi)


def isfile(fi):
	return os.path.isfile(fi)

def rmfiles(dir):
	#print(dir)
	if (isdir(dir)):
		files = glob.glob(dir+"/*")
		for f in files:
			#os.remove(f)
			rmfiles(f)
		os.rmdir(dir)
	else:
		if isfile(dir):
			os.remove(dir)

def filesize(read):
	if read != "":
		fs = open(read, 'r')
		texte = fs.read()
		longueur=len(texte)
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
	#print(f + " "+word)
	if isfile(f):
		#fs = open(f, 'r', encoding='utf8')
		with open(f, 'r', errors='ignore') as fs:
			texte = fs.read()
			n = texte.count(word)
			fs.close()
		return n
	else:
		return 0


def run_test(exe):
	print("===> run "+exe)
	if isfile(exe):
		print("run")
	else:
		msg("make ne genere pas "+exe, 0.5)	





### VERIFIE QUE SOUS LINUX
print("Python version="+sys.version)
from sys import platform
print("plateforme=" + platform)
if platform == "linux" or platform == "linux2" or platform == "win32":
	print("Vous etes sous Linux: OK")
else:
	print("Vous devez etre sous Linux !")
	sys.exit(0)




### Argument du script pour recuperer le nom du fichier
if len(sys.argv) != 2:
	print("Lancez la commande avec l'archive en parametre: " + sys.argv[0] + " NOMETU1_NOMETU2.tgz")
	sys.exit(0)

FILENAME = sys.argv[1]
NOM = FILENAME.split(".")[0]
print("FILENAME="+FILENAME)
NOTESFILE = NOM+"_notes.csv"
NOTE = 5
RETOUR = ""
print("===> note initiale="+str(NOTE))



### EXTRACTION DE L ARCHIVE
print("===> tar extraction ...")
tar = tarfile.open(FILENAME)
DIR = tar.members[0].name.split("/")[0]
#for tarinfo in tar:
#	if tarinfo.isdir():
#		print(tarinfo.name + " is dir ")
tar.extractall()
tar.close()
print("===> tar extraction ...done")



### VERIFICATION de l'arborescence
print("===> VERIFICATION de l'arborescence ...repertoire="+os.getcwd()+"/"+DIR)
ERR = "Repertoire principal introuvable; "
if not isdir(DIR):
	msg(ERR, 5)

os.chdir( os.getcwd() + "/" + DIR)

ERR = "Probleme arborescence /bin /src /doc; "	
if not isdir("bin"):
	msg( ERR, 0.5)
if not isdir("src"):
	msg( ERR, 0.5)
if not isdir("doc"):
	msg( ERR, 0.5)
if not isdir("data"):
	msg( ERR, 0.5)
print("===> VERIFICATION de l'arborescence ...done ==> note="+str(NOTE))



### MAKEFILE
print("===> Cherche le Makefile ...")
ERR = "Makefile introuvable;"
MAKEFILE = "Makefile"
if not isfile(MAKEFILE):
	MAKEFILE = "makefile"
	if not isfile(MAKEFILE):
		MAKEFILE="???"
		msg( ERR, 1)
print("===> Cherche le Makefile ...done, makefile="+ MAKEFILE+" ==> note="+str(NOTE))


print("===> make")
make_process = subprocess.run(['make'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
warning = str(make_process.stderr).count("warning:")
if warning>0:
	msg( "Il a "+str(warning)+" warnings à la compilation", min(warning*0.1, 0.5) )
error = str(make_process.stderr).count("error:")
if error>0:
	msg( "Il a "+str(error)+" erreurs à la compilation!", 1)




print("===> run prog")
run_test("bin/exemple")
run_test("bin/test")
run_test("bin/affichage")



print("===> Valgrind sur bin/exemple")
exe = "bin/exemple"

if isfile(exe):
	make_process = subprocess.run(['valgrind', exe], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	print( make_process.stderr) # ERROR SUMMARY: 0 errors

else:
	msg(exe + " n'existe pas !", 1)	





print("===> make clean")
make_process = subprocess.run(['make', 'clean'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
#print( str(make_process.stdout))
#print( str(make_process.stderr))
if isfile("bin/exemple"):
	msg( "make clean ne supprime pas bin/exemple", 0.1)	
if isfile("bin/test"):
	msg( "make clean ne supprime pas bin/test", 0.1)	
if isfile("bin/affichage"):
	msg( "make clean ne supprime pas bin/affichage", 0.1)
print("===> make clean / make / run prog...done, ==> note="+str(NOTE))



print("===> readme.txt")
readmes = [ "readme.txt", "Readme.txt", "README.txt"]
readme = filein(readmes)
if readme != "":
	longueur = filesize(readme)
	print("===> DOC : longueur du fichier "+readme+" = " + str(longueur))
	if longueur<500:
		msg( read + " de longueur < à 500 caracteres !", 0.5)
else:
	msg( "readme.txt introuvable", 1)



print("===> DOXYGEN")
doxys = [ "doc/image.dox", "doc/image.oxy", "doc/image.doxy", "doc/doxyfile"]
doxy = filein(doxys)
if doxy != "":
	rmfiles("doc/html")
	make_process = subprocess.run(['doxygen', doxy], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
	if isfile("doc/html/index.html"):
		sz = filesize("doc/html/index.html")
		if sz<1000:
			msg( "Taille de doc/html/index.html < 1000", 0.5)
	else:
		msg( "Doxgen n'a pas genere doc/html/index.html", 1)
else:
	msg( "doc/image.oxy introuvable", 1)


files = [ "src/image.h", "src/image.cpp", "src/Image.h", "src/Image.cpp" ]
search = [ "/**", "//!", "///", "//!"]
n = 0
for f in files:
	for s in search:
		n += countInFile(f,s)
print("Nombre de commentaires doxygen="+str(n))
if n<15:
	msg( "Pas assez de commentaires doxygen", 0.5)
print("===> DOXYGEN...ok")



print("===> assert...")
search = [ "assert"]
n = 0
for f in files:
	for s in search:
		n += countInFile(f,s)
print("Nombre d'assert="+str(n))
if n<15:
	msg( "Pas assez d'assert", 1)
print("===> assert...ok")



print("======================================= Recapitulatif des problemes")
print(RETOUR)
print("La note est "+str(NOTE))