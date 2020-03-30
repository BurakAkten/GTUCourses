JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
        LibraryManagmentSys.java \
        LibrarySystem.java \
        Staff.java \
        Users.java \
        mainTester.java 

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
