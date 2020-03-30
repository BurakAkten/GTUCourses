JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
        Bigram.java \
        BigramDyn.java \
        BigramMap.java \
        myPair.java \
        _mainTester.java 

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class
