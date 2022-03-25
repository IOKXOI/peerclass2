Si tu peux jeter un oeil aussi a ce GNL, quand j'utilise le testeur (<make b> dans gnlTester),
je crois comprendre que je return null sur le test "8 multiple fd" pour buffer_size=42 ou 10 000 000. 
Pourtant quand je fais mes tests je return bien '0'. Tu peux voir les test dans gnlTester/tests/bonus.cpp
et dans gnlTester/utils/check.cpp et gnl.cpp tu peux voir un peu comment il procede. 
Moi j'ai du mal a capter le CPP, donc je capte mal les tests. Je comprends pas non plus, pourquoi
si je met en commentaire le test 8, j'ai un KO sur le test 12 avec buffer_size=1. 
