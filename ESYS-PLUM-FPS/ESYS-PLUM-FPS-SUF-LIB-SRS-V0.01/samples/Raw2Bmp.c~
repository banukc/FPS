
#include "bmpconv.h"

#define FAIL 0;
#define DONE 1;

unsigned int ConvertRaw2bmp(char* rawimagepath,char* bmpfilename)
{
	//unsigned int ret;
	unsigned int i;
	unsigned long sz,status,j=0;
	bmpfileheader Fheader;
	bmpinfo info;
	FILE *RAWfile;
	FILE *BMPfile;
	unsigned char *rawbuffer, *bmpbuffer;

	RAWfile = fopen(rawimagepath, "rb");
	
	fseek(RAWfile, 0L, SEEK_END);
	sz = ftell(RAWfile);
	fseek(RAWfile, 0L, SEEK_SET);

	rawbuffer=(unsigned char *)malloc(sz);

	if(rawbuffer == NULL)
	{
		printf("\nMemory Allocation Failed..\n");
		return FAIL;
	}
	bmpbuffer=(unsigned char *)malloc(sz+1078);
	
	if(bmpbuffer == NULL)
	{
		printf("\nMemory Allocation Failed..\n");
		return FAIL;
	}
	
	status = fread(rawbuffer,1,sz,RAWfile);
	if(status != sz)
	{
		printf("\nFile Read Error\n");
		return FAIL;
	}
	
	Fheader.bmid0 = 'B';
	Fheader.bmid1 = 'M';
	Fheader.filesize = (sz+1078-12);
	Fheader.rfu = 0;
	Fheader.bmoffset = 1078;

	info.headersize = 40;
	info.hor_width = (unsigned int)((rawbuffer[5]<<8)|rawbuffer[4]);
	info.ver_width = (unsigned int)((rawbuffer[3]<<8)|rawbuffer[2]);
	info.planes = 1;
	info.bpp = rawbuffer[11];
	info.comptype = 0;
	info.imagesize = 0;
	info.hor_res = 0;
	info.ver_res = 0;
	info.used_colors = 0;
	info.imp_colors = 0;

	bmpbuffer[0] = 'B';
	bmpbuffer[1] = 'M';
	bmpbuffer[2] = (unsigned char)(Fheader.filesize);
	bmpbuffer[3] = (unsigned char)(Fheader.filesize>>8);
	bmpbuffer[4] = (unsigned char)(Fheader.filesize>>16);
	bmpbuffer[5] = (unsigned char)(Fheader.filesize>>24);
	bmpbuffer[6] = (unsigned char)Fheader.rfu;
	bmpbuffer[7] = (unsigned char)Fheader.rfu;
	bmpbuffer[8] = (unsigned char)Fheader.rfu;
	bmpbuffer[9] = (unsigned char)Fheader.rfu;
	bmpbuffer[10] = (unsigned char)(Fheader.bmoffset);
	bmpbuffer[11] = (unsigned char)(Fheader.bmoffset>>8);
	bmpbuffer[12] = (unsigned char)(Fheader.bmoffset>>16);
	bmpbuffer[13] = (unsigned char)(Fheader.bmoffset>>24);

	bmpbuffer[14] = (unsigned char)(info.headersize);
	bmpbuffer[15] = (unsigned char)(info.headersize>>8);
	bmpbuffer[16] = (unsigned char)(info.headersize>>16);
	bmpbuffer[17] = (unsigned char)(info.headersize>>24);
	bmpbuffer[18] = (unsigned char)(info.hor_width);
	bmpbuffer[19] = (unsigned char)(info.hor_width>>8);
	bmpbuffer[20] = (unsigned char)(info.hor_width>>16);
	bmpbuffer[21] = (unsigned char)(info.hor_width>>24);
	bmpbuffer[22] = (unsigned char)(info.ver_width);
	bmpbuffer[23] = (unsigned char)(info.ver_width>>8);	
	bmpbuffer[24] = (unsigned char)(info.ver_width>>16);
	bmpbuffer[25] = (unsigned char)(info.ver_width>>24);
	bmpbuffer[26] = (unsigned char)(info.planes);
	bmpbuffer[27] = (unsigned char)(info.planes>>8);
	bmpbuffer[28] = (unsigned char)(info.bpp);
	bmpbuffer[29] = (unsigned char)(info.bpp>>8);
	bmpbuffer[30] = (unsigned char)(info.comptype);
	bmpbuffer[31] = (unsigned char)(info.comptype>>8);
	bmpbuffer[32] = (unsigned char)(info.comptype>>16);
	bmpbuffer[33] = (unsigned char)(info.comptype>>24);
	bmpbuffer[34] = (unsigned char)(info.imagesize);
	bmpbuffer[35] = (unsigned char)(info.imagesize>>8);
	bmpbuffer[36] = (unsigned char)(info.imagesize>>16);
	bmpbuffer[37] = (unsigned char)(info.imagesize>>24);
	bmpbuffer[38] = (unsigned char)(info.hor_res);
	bmpbuffer[39] = (unsigned char)(info.hor_res>>8);
	bmpbuffer[40] = (unsigned char)(info.hor_res>>16);
	bmpbuffer[41] = (unsigned char)(info.hor_res>>24);
	bmpbuffer[42] = (unsigned char)(info.ver_res);
	bmpbuffer[43] = (unsigned char)(info.ver_res>>8);
	bmpbuffer[44] = (unsigned char)(info.ver_res>>16);
	bmpbuffer[45] = (unsigned char)(info.ver_res>>24);
	bmpbuffer[46] = (unsigned char)(info.used_colors);
	bmpbuffer[47] = (unsigned char)(info.used_colors>>8);
	bmpbuffer[48] = (unsigned char)(info.used_colors>>16);
	bmpbuffer[49] = (unsigned char)(info.used_colors>>24);
	bmpbuffer[50] = (unsigned char)(info.imp_colors);
	bmpbuffer[51] = (unsigned char)(info.imp_colors>>8);
	bmpbuffer[52] = (unsigned char)(info.imp_colors>>16);
	bmpbuffer[53] = (unsigned char)(info.imp_colors>>24);

	j=54;
	for(i=0;i<=255;i++)
	{
		bmpbuffer[j++] = i;
		bmpbuffer[j++] = i;
		bmpbuffer[j++] = i;
		bmpbuffer[j++] = 0;
	}

	memcpy(bmpbuffer+j,rawbuffer+12,sz-12);
	
	BMPfile = fopen(bmpfilename, "wb");
	fwrite(bmpbuffer,1,Fheader.filesize,BMPfile);

	fclose(BMPfile);
	fclose(RAWfile);

	free(rawbuffer);
	free(bmpbuffer);


	return DONE;
}
