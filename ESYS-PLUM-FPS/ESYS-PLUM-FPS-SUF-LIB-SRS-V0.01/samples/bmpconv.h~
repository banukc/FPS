
typedef struct BMPFHDR{
	unsigned char bmid0,bmid1;
	unsigned int filesize;
	unsigned int rfu;
	unsigned int bmoffset;
}bmpfileheader;

typedef struct BMINFOHEADER{
	unsigned int headersize;
	unsigned int hor_width;
	unsigned int ver_width;
	unsigned short planes;
	unsigned short bpp;
	unsigned int comptype;
	unsigned int imagesize;
	unsigned int hor_res;
	unsigned int ver_res;
	unsigned int used_colors;
	unsigned int imp_colors;
}bmpinfo;

unsigned int ConvertRaw2bmp(char* rawimagepath,char* bmpfilename);
