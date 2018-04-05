all:	gtk3test.c
	export PKG_CONFIG_PATH=/opt/gtk3-win64/lib/pkgconfig
	gcc gtk3test.c -o gtktest.out 'pkg-config --cflags --libs gtk+-3.0'
