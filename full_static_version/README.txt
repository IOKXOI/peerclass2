Pour compiler le programme avec le testeur, aller dans le dossier gnl testeur et <make m>. En creant un tableau de 100 FDet en compilant avec BUFFER_SIZE=10 000 000, ca timeout juste. Je pensais que ca nous faisait un tableau de 1milliards de char. Par contre quand on change pour creer un tableau de 256, on a ce message direct pour BUFFER_SIZE=42: 
"valgrind: mmap(0x411000, 2560000000) failed in UME with error 22 (Invalid argument).
valgrind: this can be caused by executables with very large text, data or bss segments.
make: *** [Makefile:48: 10Mmandatory] Error 1 "
J'ai cru comprendre que ce message c'etait parce qu'on a un trop grand tableau dans la memoire BSS. Mais dans le deuxieme cas on a un tableau de seulement 10 752 alors qu'on a pas le message pour un tableau de 1milliard. 

Si tu veux changer les valeurs, t'as le define dans le get_next_line.c
