
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>
#include  <fcntl.h>
#include "libMSO.h"
#include "Ilv_definitions.h"
#include "MSO_FPS.h"
#include "MSO_Command.c"
#include "MSO_Connect.c"
#include "libMSO_Struct.h"
#include "Raw2Bmp.c"

UCHAR 	i_uc_PkFormat;
MORPHO_HANDLE g_h_Mso100Handle;

int main(int argc,char *argv[])
{
	int i;
	I l_i_i;
	
	UC l_uc_loop;
	UL no_finger=1;
	UL	l_ul_nbFingers;
	US time_out=0;
	UL uc_NbPkRef=1;
	T_EXPORT_PK l_x_ExportPk[10];
	T_EXPORT_IMAGE l_x_ExportImage;
	
	C	l_ac_buffer[INPUT_BUFFER_SIZE];		
	// Initialisation
	
	
	UL AsynchronousEvnt;
	AsynchronousEvnt = MORPHO_CALLBACK_DETECTQUALITY |
		MORPHO_CALLBACK_CODEQUALITY |
		MORPHO_CALLBACK_IMAGE_CMD |
		MORPHO_CALLBACK_COMMAND_CMD | MORPHO_CALLBACK_ENROLLMENT_CMD;	

	// banner
	show_banner ();
	
	//MSO_Connection
	
	MSOconnection();	

	// Register Asynchronous event Callback Function
	
	MSORegisterAsyncILV(AsynchronousEvnt);

	// main loop
	l_uc_loop = 1;
	while (l_uc_loop)
	{	
		switch ((l_i_i = CommandMenu ()))
		{
			default:
				fprintf (stdout, "unrecognize command: %d\n", l_i_i);
				break;

			case 0:
				l_uc_loop = 0;
				break;
			case 1:
				// Capture
					
					i_uc_PkFormat= getTemplateType();
					getUserInput(l_ac_buffer, "number of fingers to Capture:\n");
					sscanf(l_ac_buffer, "%ld", &l_ul_nbFingers);
					for(i=0;i<l_ul_nbFingers;i++)
					{
						l_x_ExportPk[i].io_px_BiometricData = malloc (1 * sizeof (T_BUF));
						l_x_ExportPk[i].i_uc_ExportMinutiae = 1;
					
						l_x_ExportPk[i].io_px_BiometricData[0].m_ul_Size = 512;
						l_x_ExportPk[i].io_px_BiometricData[0].m_puc_Buf = malloc (512);
						memset (l_x_ExportPk[i].io_px_BiometricData[0].m_puc_Buf, 0, 512);
					ucFPSCaptureTemplate(no_finger,time_out,AsynchronousEvnt,i_uc_PkFormat,l_x_ExportPk[i]);			
					}
			
			  		
				break;
	
			case 2:
				// Verify
				
					i_uc_PkFormat= verifyTemplateType();
					no_finger=1;	
					ucFPSVerifyTemplate(no_finger,time_out,AsynchronousEvnt,l_x_ExportPk,i_uc_PkFormat);
				break;
	
			case 3:
					
				//verify match

					i_uc_PkFormat= verifyTemplateType();
					ucFPSVerifyMatch(uc_NbPkRef,l_x_ExportPk,i_uc_PkFormat);
				break;
			
			case 4:
				
				// Verify Many
					i_uc_PkFormat= verifyTemplateType();
					no_finger=l_ul_nbFingers;								
					ucFPSVerifyMany(no_finger,time_out,AsynchronousEvnt,l_x_ExportPk,i_uc_PkFormat);
				break;

			case 5:
				
				// Get image
					i_uc_PkFormat= getTemplateType();

					l_x_ExportImage.io_px_BufImage = malloc (1 * sizeof (T_BUF));
					l_x_ExportImage.i_uc_ExportImageType = 0;
	
					for (l_i_i = 0; l_i_i < 1; l_i_i++)
					{
						l_x_ExportImage.io_px_BufImage[l_i_i].m_ul_Size = 416 * 416 + 12;
						l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf =malloc (416 * 416 + 12);
						memset (l_x_ExportImage.io_px_BufImage[l_i_i].m_puc_Buf,0, 416 * 416 + 12);
					}
					
					ucGetFingerImage(no_finger,time_out,AsynchronousEvnt,i_uc_PkFormat,l_x_ExportImage);
				break;
	
			case 6: 
				
				//get serial number
					ucGetSerialNum();
		}
	}

	// Disconnect to MSO
	MSOCloseCom();

	return SUCCESS;
}

/***************************************image conversion************************************/

I SaveBufIn_image (PT_BUF i_px_Buf)
{
	FILE *fp;
	PC i_pc_Ext =".raw";
	C l_ac_String[256];
	I l_i_Ret;
	C filename[256];
	char *ext=".bmp";	
	
	
	fprintf (stdout, "Enter File name : -> ");
	fgets (l_ac_String, 256, stdin);
	
	l_ac_String[strlen (l_ac_String) - 1] = 0;	// Suppress '\n' 
	if (strstr (l_ac_String, i_pc_Ext) == NULL)
		strcat (l_ac_String, i_pc_Ext);
	
	fp = fopen (l_ac_String, "wb");
	if (fp != NULL)
	{
		l_i_Ret = fwrite (i_px_Buf->m_puc_Buf, 1, i_px_Buf->m_ul_Size, fp);
		fclose (fp);
		
		fprintf (stdout, "--> Save %d bytes in %s\n", l_i_Ret, l_ac_String);
		
	}
	else
	{
		fprintf (stdout, "Can't open file %s for writing\n", l_ac_String);
	}
					
		fprintf (stdout, "Enter File name : -> ");
		fgets (filename, 256, stdin);

		filename[strlen (filename) - 1] = 0; 
		if (strstr (filename, ext) == NULL)
		
		strcat (filename, ext);

		printf(" Image file name %s \n",filename);
		ConvertRaw2bmp(l_ac_String,filename);


	return 0;
}


/**********************************command menu*******************************************/
I CommandMenu ()
{
	C l_ac_string[32];
	I l_i_i = 0;
	
		fprintf (stdout, "-------------------- MSO ILV Command ----------------\n");
		fprintf (stdout, "\tCapture                                      --->(1)\n");
		fprintf (stdout, "\tVerify                                       --->(2)\n");
		fprintf (stdout, "\tVerify Match                                 --->(3)\n");
		fprintf (stdout, "\tverify many	                                 --->(4)\n");
		fprintf (stdout, "\tGet image                           	 --->(5)\n");
		fprintf (stdout, "\tGet serial number                            --->(6)\n");
		fprintf (stdout, "\tQuit                                         --->(0)\n");
	
		fprintf (stdout, "Select -> ");
		while (1)
		{
			if (fgets (l_ac_string, 32, stdin) == NULL)
			{
				fprintf (stdout, "->Error\n");
				return -1;
			}
			if (sscanf (l_ac_string, "%d", &l_i_i) == 1)
			{
				if (l_i_i >= 0 && l_i_i <= 6)
				break;
			}
			fprintf (stdout, "Select -> ");
		}
	return l_i_i;
}






