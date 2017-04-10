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
#include "libMSO_Struct.h"


#define FPS_VERSION	"1.0"
#define INPUT_BUFFER_SIZE 128

#define DEFAULT_SERIAL_PORT		"/dev/ttyS0"
#define DEFAULT_BAUD_RATE		115200

MORPHO_HANDLE g_h_Mso100Handle;

UC g_uc_ExportScore;
UCHAR 	i_uc_PkFormat;

/*********************************show banner********************************************/
void show_banner (void)
{
	fprintf (stdout, "\n--------------------------------------------------\n");
	fprintf (stdout, "MSO_FPS program - Version %s\nCompiled: " __DATE__
					 "\n", FPS_VERSION);
	fprintf (stdout, "--------------------------------------------------\n\n");
}

/*********************************command call back****************************************/
I CommandCallback (PVOID i_pv_context, I i_i_command, PVOID i_pv_param)
{
	T_MORPHO_CALLBACK_IMAGE_STATUS l_x_ImageStructure;
	PUC l_puc_EnrollmentCmd;
	C l_c_String[256];
	UC l_uc_quality;

	if (i_i_command == MORPHO_CALLBACK_COMMAND_CMD)
	{
		switch (*((PI) i_pv_param))
		{
		case MORPHO_REMOVE_FINGER:
		break;
		case MORPHO_MOVE_NO_FINGER:
		break;
		case MORPHO_LATENT:
		break;
		case MORPHO_MOVE_FINGER_UP:
		break;
		case MORPHO_MOVE_FINGER_DOWN:
		break;
		case MORPHO_MOVE_FINGER_LEFT:
		break;
		case MORPHO_MOVE_FINGER_RIGHT:
		break;
		case MORPHO_PRESS_FINGER_HARDER:
		break;
		case MORPHO_FINGER_OK:
		break;
		default:
		fprintf (stdout, "Async message %d\n", *(PI) i_pv_param);
		break;
		}
	}

	if (i_i_command == MORPHO_CALLBACK_ENROLLMENT_CMD)
	{
		l_puc_EnrollmentCmd = (PUC) i_pv_param;
		switch (l_puc_EnrollmentCmd[0])
		{
			case 1:
				switch (l_puc_EnrollmentCmd[2])
				{
					case 1:
						sprintf (l_c_String,
							"Place Right Forefinger -> Capture %d/%d",
							l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
						
					break;
				
					case 2:
						sprintf (l_c_String,
							"Right Forefinger Again -> Capture %d/%d",
							l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
						
					break;
				
					case 3:
						sprintf (l_c_String,
							"Right Forefinger Again -> Capture %d/%d",
							l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
						
					break;
				}
			break;
	
			case 2:
				switch (l_puc_EnrollmentCmd[2])
				{
					case 1:
						sprintf (l_c_String,
							"Place Left Forefinger -> Capture %d/%d",
							l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
						
					break;
		
				case 2:
						sprintf (l_c_String,
							"Left Forefinger Again -> Capture %d/%d",
							l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
					
					break;
		
				case 3:
					sprintf (l_c_String,
						"Left Forefinger Again -> Capture %d/%d",
						l_puc_EnrollmentCmd[2], l_puc_EnrollmentCmd[3]);
					
				break;
				}
			break;
		}
	}

	if (i_i_command == MORPHO_CALLBACK_IMAGE_CMD)
	{
		memcpy (&l_x_ImageStructure.m_x_ImageHeader,
			(T_MORPHO_IMAGE_HEADER *) i_pv_param,
			sizeof (T_MORPHO_IMAGE_HEADER));
		l_x_ImageStructure.m_puc_Image =
		(PUC) i_pv_param + sizeof (T_MORPHO_IMAGE_HEADER);
	}

	if (i_i_command == MORPHO_CALLBACK_CODEQUALITY)
	{
		l_uc_quality = *(PUC) i_pv_param;
		sprintf (l_c_String, "Code Quality : %d", l_uc_quality);
		
	}
	
	if (i_i_command == MORPHO_CALLBACK_DETECTQUALITY)
	{
		l_uc_quality = *(PUC) i_pv_param;
		sprintf (l_c_String, "Detect Quality : %d", l_uc_quality);
		
	}

	return 0;
}



/*************************************image data compression**************************************/
I image_data_compression()
{
	C l_ac_string[32];
	I l_j_j = 0;
		fprintf (stdout, "--------------MSO image compression command ----------\n");
		fprintf (stdout, "\tUncompress_image                              --->(1)\n");
		fprintf (stdout, "\tCompress_image                                --->(2)\n");

		fprintf (stdout, "Select -> ");
		while (1)
		{
			if (fgets (l_ac_string, 32, stdin) == NULL)
			{
				fprintf (stdout, "->Error\n");
				return -1;
			}
			if (sscanf (l_ac_string, "%d", &l_j_j) == 1)
			{
				if (l_j_j >= 0 && l_j_j <= 2)
				break;
			}
			fprintf (stdout, "Select -> ");
		}
	return l_j_j;
}


/******************************************PK Format**************************************************/

UCHAR getTemplateType()
{
	C						l_ac_buffer[INPUT_BUFFER_SIZE];
	I						l_i_TypeTemplateChoice;
	INT	i_uc_PkFormat ;

	getUserInput(l_ac_buffer, "\n\nTemplate type menu:\n"
								"1  - PK_COMP\n"
								"2  - PK_MAT_NORM\n"
								"3  - PK_COMP_NORM\n"
								"4  - PK_MAT\n"
								"5  - PK_ANSI_378\n"
								"6  - PK_MINEX_A\n"
								"7  - PK_ISO_FMR\n"
								"8 - PK_ISO_FMC_NS\n"
								"9 - PK_ISO_FMC_CS\n"
								"0  - PKLITE\n"
								"Any other - PK_CFV\n");
	sscanf(l_ac_buffer, "%d", &l_i_TypeTemplateChoice);

	switch (l_i_TypeTemplateChoice )
	{
		case 1:
			i_uc_PkFormat =MORPHO_PK_COMP;
			break;
		case 2:
			i_uc_PkFormat = MORPHO_PK_MAT_NORM;
			break;
		case 3:
			i_uc_PkFormat = MORPHO_PK_COMP_NORM;
			break;
		case 4:
			i_uc_PkFormat = MORPHO_PK_MAT;
			break;
		case 5:
			i_uc_PkFormat = MORPHO_PK_ANSI_378;
			break;
		case 6:
			i_uc_PkFormat = MORPHO_PK_MINEX_A;
			break;
		case 7:
			i_uc_PkFormat = MORPHO_PK_ISO_FMR;
			break;
		case 8:
			i_uc_PkFormat = MORPHO_PK_ISO_FMC_NS;
			break;
		case 9:
			i_uc_PkFormat = MORPHO_PK_ISO_FMC_CS;
			break;
		
		case 10:
			i_uc_PkFormat = MORPHO_PK_PKLITE;
			break;
		default:
			i_uc_PkFormat = MORPHO_PK_CFV;
			break;
	}

	return i_uc_PkFormat;
}


UCHAR verifyTemplateType()
{
	C						l_ac_buffer[INPUT_BUFFER_SIZE];
	I						TypeTemplateChoice;
	INT uc_PkFormat ;

	getUserInput(l_ac_buffer, "\n\nTemplate type menu:\n"
								"1  - PK_COMP\n"
								"2  - PK_MAT_NORM\n"
								"3  - PK_COMP_NORM\n"
								"4  - PK_MAT\n"
								"5  - PK_ANSI_378\n"
								"6  - PK_MINEX_A\n"
								"7  - PK_ISO_FMR\n"
								"8 - PK_ISO_FMC_NS\n"
								"9 - PK_ISO_FMC_CS\n"
								"0  - PKLITE\n"
								"Any other - PK_CFV\n");
	sscanf(l_ac_buffer, "%d", &TypeTemplateChoice);

	sscanf(l_ac_buffer, "%d", &TypeTemplateChoice);

	switch (TypeTemplateChoice )
	{
		case 1:
			uc_PkFormat = 0x02;
			break;
		case 2:
			uc_PkFormat = 0x35;
			break;
		case 3:
			uc_PkFormat = 0x37;
			break;
		case 4:
			uc_PkFormat = 0x03;
			break;
		case 5:
			uc_PkFormat = MORPHO_PK_ANSI_378;
			break;
		case 6:
			uc_PkFormat = MORPHO_PK_MINEX_A;
			break;
		case 7:
			uc_PkFormat = MORPHO_PK_ISO_FMR;
			break;
		case 8:
			uc_PkFormat = MORPHO_PK_ISO_FMC_NS;
			break;
		case 9:
			uc_PkFormat = MORPHO_PK_ISO_FMC_CS;
			break;
		
		case 10:
			uc_PkFormat = MORPHO_PK_PKLITE;
			break;
		default:
			uc_PkFormat = MORPHO_PK_CFV;
			break;
	}

	return uc_PkFormat;
}

/************************************Get User********************************************/

I getUserInput(char o_auc_buffer[INPUT_BUFFER_SIZE], const char*message)
{
	fprintf(stdout, "%s", message);
	fgets(o_auc_buffer, INPUT_BUFFER_SIZE, stdin);
	o_auc_buffer[strlen(o_auc_buffer) - 1] = '\0';	// Remove trailing \n

	return 0;
}

/***************************************MSO_RegisterAsyncILV**********************************/

UCHAR MSORegisterAsyncILV(ULONG AsynchronousEvnt)
{
	I l_i_Ret;

			l_i_Ret= MSO_RegisterAsyncILV( g_h_Mso100Handle, 
						AsynchronousEvnt,
						(T_pFuncILV_Buffer) CommandCallback,
						NULL );

			if ((l_i_Ret != 0) || (g_h_Mso100Handle == NULL))
			{
				return FAILURE;
			}

	return SUCCESS;
}
/**************************************MSOCloseCom**********************************************/

UCHAR MSOCloseCom()
{
	I l_i_Ret;

			l_i_Ret = MSO_CloseCom (&g_h_Mso100Handle);
			if (l_i_Ret != RETURN_NO_ERROR)
			{
				fprintf (stdout, "Error MSO_CloseCom\n");
			}

	return SUCCESS;	
}

/*****************************************MSO_Connection******************************************/

UCHAR MSOconnection()
{
	I l_i_speed;
	C l_ac_Device[32];
	l_i_speed = DEFAULT_BAUD_RATE;
	int l_i_IdProduct;
	UC l_uc_ConnectionType;
	l_uc_ConnectionType = 0;
	I l_i_Ret;
	sprintf (l_ac_Device, "%s", DEFAULT_SERIAL_PORT);
	
			// Connection to MSO 
			l_i_Ret = MSO_Connect( &g_h_Mso100Handle, 
							l_uc_ConnectionType, 
							l_ac_Device,
							l_i_speed, 
							&l_i_IdProduct);
			if ((l_i_Ret != 0) || (g_h_Mso100Handle == NULL))
			{
				fprintf (stdout, "Error Connection\n");
				return FAILURE;
			}

	return SUCCESS;
}

/***************************************FPS Capture template**************************************************/

UCHAR ucFPSCaptureTemplate(ULONG nbFingers,USINT usTimeOut,ULONG AsynchronousEvnt,UCHAR PkFormat,T_EXPORT_PK ExportPk)
{
	INT l_i_Ret;		

			
			l_i_Ret=capture( g_h_Mso100Handle, 
					   AsynchronousEvnt,
					   usTimeOut,
					   &ExportPk,
					   PkFormat,
					   NULL,
					    nbFingers
						);
	
			if (AsynchronousEvnt > 0)
			{
				MSO_UnregisterAllAsyncILV (g_h_Mso100Handle);
				AsynchronousEvnt = 0;
			}

			if ((l_i_Ret != 0) || (g_h_Mso100Handle == NULL))
			{
				return FAILURE;
			}

			
	return SUCCESS;
}

/************************************FPS Verify Template*************************************************/

UCHAR ucFPSVerifyTemplate(ULONG nbFingers,USINT usTimeOut,ULONG AsynchronousEvnt,PT_EXPORT_PK ExportPk,UCHAR PkFormat)
{
	
	INT l_i_i;
	T_BUF_PK i_px_Buf_Pk[nbFingers];		
	INT l_i_Ret;		
			
			
			for (l_i_i = 0; l_i_i < nbFingers; l_i_i++)
			{
				i_px_Buf_Pk[l_i_i].m_x_Buf.m_ul_Size = 512;
				i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf = malloc (512);
				memset (i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf, 0, 512);
	
				i_px_Buf_Pk[l_i_i].m_uc_IdPk = PkFormat; //PKCOMP
				
				i_px_Buf_Pk[l_i_i].m_uc_Index =0;
				
				memcpy(i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf,ExportPk[l_i_i].io_px_BiometricData[0].m_puc_Buf,
									   ExportPk[l_i_i].io_px_BiometricData[0].m_ul_Size);
				i_px_Buf_Pk[l_i_i].m_x_Buf.m_ul_Size = ExportPk[l_i_i].io_px_BiometricData[0].m_ul_Size;
      			}
			
			
			if (AsynchronousEvnt > 0)
			{
				MSO_UnregisterAllAsyncILV (g_h_Mso100Handle);
				AsynchronousEvnt = 0;
			}
	
				
			l_i_Ret=Verify( g_h_Mso100Handle,
				i_px_Buf_Pk,
				nbFingers,
				AsynchronousEvnt,
				usTimeOut);


			for (l_i_i = 0; l_i_i < nbFingers; l_i_i++)
			{
				if (i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf != NULL)
				    free (i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf);
			}
	
			if ((l_i_Ret != 0) || (g_h_Mso100Handle == NULL))
			{
				return FAILURE;
			}
			
	return SUCCESS;				
}

/***************************************FPS Verify Match****************************************/

UCHAR ucFPSVerifyMatch(ULONG NbPkRef,PT_EXPORT_PK ExportPk,UCHAR PkFormat)
{

	INT l_i_Ret;
	INT l_i_i;
	T_BUF_PK i_px_Buf_Pk[2];
	
			for (l_i_i = 0; l_i_i < 2; l_i_i++)
			{
				i_px_Buf_Pk[l_i_i].m_x_Buf.m_ul_Size = 512;
				i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf = malloc (512);
				memset (i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf, 0, 512);
	
				i_px_Buf_Pk[l_i_i].m_uc_IdPk = PkFormat; //PKCOMP
				i_px_Buf_Pk[l_i_i].m_uc_Index =0;
		
				memcpy(i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf,ExportPk[l_i_i].io_px_BiometricData[0].m_puc_Buf,
									ExportPk[l_i_i].io_px_BiometricData[0].m_ul_Size);
				i_px_Buf_Pk[l_i_i].m_x_Buf.m_ul_Size =  ExportPk[l_i_i].io_px_BiometricData[0].m_ul_Size;
			}
	
			l_i_Ret=VerifyMatch(g_h_Mso100Handle, 
				    & i_px_Buf_Pk[0],
			            & i_px_Buf_Pk[1],
				     NbPkRef);

			for (l_i_i = 0; l_i_i < 2; l_i_i++)
			{
					if (i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf != NULL)
					free (i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf);
			}
					
			if ((l_i_Ret != 0) || (g_h_Mso100Handle == NULL))
			{
				return FAILURE;
			}

	return SUCCESS;						
}

/*****************************Get Finger Image***********************************************************/

UCHAR ucGetFingerImage(ULONG nbFingers,USINT usTimeOut,ULONG AsynchronousEvnt,UCHAR PkFormat,T_EXPORT_IMAGE ExportImage)
{
	INT l_j_j; 
	INT l_i_i;
	INT l_i_Ret;	
	T_MORPHO_IMAGE_HEADER ImgHdr;
			
			switch ((l_j_j =image_data_compression()))
				{
					default:
						fprintf (stdout, "unrecognize command: %d\n", l_j_j);
					break;
	
					case 1:
						// Uncompress image
						ExportImage.i_uc_CompressionType = ID_COMPRESSION_NULL;
					break;
			
					case 2:
						// Compress image
						ExportImage.i_uc_CompressionType = ID_COMPRESSION_V1;
					break;

				  }
					
			l_i_Ret=capture( g_h_Mso100Handle, 
					   AsynchronousEvnt,
					   usTimeOut,
					   NULL,
					   PkFormat,
					   &ExportImage,
					   nbFingers
					);

	
			if (AsynchronousEvnt > 0)
			{
				MSO_UnregisterAllAsyncILV (g_h_Mso100Handle);
				AsynchronousEvnt = 0;
			}
				
				
			if (l_i_Ret == 0)
			{

				SaveBufIn_image(&ExportImage.io_px_BufImage[0]);
			
				memcpy ((PUC) & ImgHdr,
				ExportImage.io_px_BufImage->m_puc_Buf,sizeof (T_MORPHO_IMAGE_HEADER));
				fprintf (stdout, "\n---- Image Header Information ----\n");
				fprintf (stdout, "Header Revision:  %d\n",ImgHdr.m_uc_HeaderRevision);
				fprintf (stdout, "Header size:      %d\n",ImgHdr.m_uc_HeaderSize);
				fprintf (stdout, "Nb Row:           %d\n", ImgHdr.m_us_NbRow);
				fprintf (stdout, "Nb Col:           %d\n", ImgHdr.m_us_NbCol);
				fprintf (stdout, "Compression Type: %d\n",ImgHdr.m_uc_CompressionType);
			}
	
			for (l_i_i = 0; l_i_i < 1; l_i_i++)
			{
				if (ExportImage.io_px_BufImage[l_i_i].m_puc_Buf != NULL)
				free (ExportImage.io_px_BufImage[l_i_i].m_puc_Buf);
			}
			if (ExportImage.io_px_BufImage != NULL)
			free (ExportImage.io_px_BufImage);
	return SUCCESS;
}

/************************************Get Serial Number**********************************************/

UCHAR ucGetSerialNum()
{
	
	INT l_i_Ret;	
	UCHAR                   	l_uc_Status;
	UCHAR                   	l_auc_DescProduct[1024];
	UCHAR                   	l_auc_DescSensor[1024];
	UCHAR                   	l_auc_DescSoftware[1024];
	UCHAR				l_auc_SerialNumber[MSO_SERIAL_NUMBER_LEN+1];
	UCHAR				l_uc_SecuConfig;
	US				l_us_SecuMaxFAR;

	memset(l_auc_SerialNumber, 0, MSO_SERIAL_NUMBER_LEN+1);

	 l_i_Ret = MSO_GetDescriptor( g_h_Mso100Handle,
                                      ID_FORMAT_TEXT,                  //UC      i_uc_DescFormat,
                                      &l_uc_Status,       		  //PUC     o_puc_ILV_Status,
                                      l_auc_DescProduct,               //VOID*   i_pv_DescProduct,
                                      1024,                            //UL      i_ul_SizeOfDescProduct,
                                      l_auc_DescSensor,                //VOID*   i_pv_DescSensor,
                                      1024,                            //UL      i_ul_SizeOfDescSensor,
                                      l_auc_DescSoftware,              //VOID*   i_pv_DescSoftware,
				      1024                             //UL      i_ul_SizeOfDescSoftware
                              		);
			
				if( (l_i_Ret == RETURN_NO_ERROR) && (l_uc_Status == ILV_OK))
   				 {
        				fprintf(stdout, "\n----------------------------\n");
        				fprintf(stdout, "MSO_GetDescriptor:\n");
        				fprintf(stdout, "-->Product:\n%s\n",l_auc_DescProduct);
        				fprintf(stdout, "-->Sensor:\n%s\n",l_auc_DescSensor);
        				fprintf(stdout, "-->Software:\n%s\n",l_auc_DescSoftware);
    				}
    				else
    				{
        				fprintf(stdout, "Error MSO_GetDescriptor\n");
					ConvertError(l_uc_Status);
    				}

				l_i_Ret = MSO_SECU_GetSerialNumber( g_h_Mso100Handle,
        							l_auc_SerialNumber,	//UC  o_auc_SerialNumber[MSO_SERIAL_NUMBER_LEN],
        							&l_uc_SecuConfig,	//PUC o_puc_SecuConfig,
        							&l_us_SecuMaxFAR,	//PUS o_pus_SecuMaxFAR,
        							&l_uc_Status		//PUC o_puc_ILV_Status
				      				);					
				if( (l_i_Ret == RETURN_NO_ERROR) && (l_uc_Status == ILV_OK))
  				 {
       					fprintf(stdout, "\n----------------------------\n");
       					fprintf(stdout, "MSO Get Security configuration:\n");
       					fprintf(stdout, "-->Serial Number:%s\n", l_auc_SerialNumber);
        				fprintf(stdout, "-->SecuConfig: 0x%02X\n",l_uc_SecuConfig);
				if(l_uc_SecuConfig & SECU_TUNNELING)
           				fprintf(stdout, "\tThe MorphoSmart uses the tunneling protocol\n");
				if(l_uc_SecuConfig & SECU_OFFERED_SECURITY)
           				fprintf(stdout, "\tThe MorphoSmart uses the offered security protocol\n");
				else
           				fprintf(stdout, "\tThe Communication is not secured\n");

       				if(l_uc_SecuConfig & 0x10)
           				fprintf(stdout, "\tThe MorphoSmart never export its matching score\n");
				else
           				fprintf(stdout, "\tThe MorphoSmart can export its matching score\n");
        				fprintf(stdout, "-->SecuMaxFAR: %d\n",l_us_SecuMaxFAR);
        				fprintf(stdout, "----------------------------\n\n");                        
   				 }
   				else
   				 {
     					 fprintf(stdout, "Error MSO_GetDescriptor\n");
					 ConvertError(l_uc_Status);
   				 }
    				l_i_Ret = MSO_CloseCom( &g_h_Mso100Handle);
    				if(l_i_Ret != RETURN_NO_ERROR) 
    				{
        				fprintf(stdout, "Error MSO_CloseCom\n");

  				}
	return SUCCESS;
}

/*************************************FPS Verify Many***********************************************/

UCHAR ucFPSVerifyMany(ULONG nbFingers,USINT usTimeOut,ULONG AsynchronousEvnt,PT_EXPORT_PK ExportPk,UCHAR PkFormat)
{

	INT l_i_Ret;
	INT l_i_i;	
	T_BUF_PK i_px_Buf_Pk[nbFingers];
					
				for (l_i_i = 0; l_i_i < nbFingers; l_i_i++)
				{
				i_px_Buf_Pk[l_i_i].m_x_Buf.m_ul_Size = 512;
				i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf = malloc (512);
				memset (i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf, 0, 512);
	
				i_px_Buf_Pk[l_i_i].m_uc_IdPk = PkFormat; //PKCOMP
				i_px_Buf_Pk[l_i_i].m_uc_Index=l_i_i;
					
				memcpy(i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf,ExportPk[l_i_i].io_px_BiometricData[0].m_puc_Buf,
									   ExportPk[l_i_i].io_px_BiometricData[0].m_ul_Size);
				i_px_Buf_Pk[l_i_i].m_x_Buf.m_ul_Size = ExportPk[l_i_i].io_px_BiometricData[0].m_ul_Size;
				
				}
				
				if (AsynchronousEvnt > 0)
				{
					MSO_UnregisterAllAsyncILV (g_h_Mso100Handle);
					AsynchronousEvnt = 0;
				}
				
				l_i_Ret=Verify( g_h_Mso100Handle,
						i_px_Buf_Pk,
						nbFingers,
						AsynchronousEvnt,
						usTimeOut);

				for (l_i_i = 0; l_i_i < nbFingers; l_i_i++)
				{
					if (i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf != NULL)
				    	free (i_px_Buf_Pk[l_i_i].m_x_Buf.m_puc_Buf);
				}

				if ((l_i_Ret != 0) || (g_h_Mso100Handle == NULL))
				{
					return FAILURE;
				}
				
	return SUCCESS;			
}





