
#define INPUT_BUFFER_SIZE 128

typedef int 			INT;
typedef unsigned long    	ULONG;
typedef unsigned char 		UCHAR;
typedef unsigned short  	USINT;

#define SUCCESS 0;
#define FAILURE 1;


int MSO_Connect( MORPHO_HANDLE * i_h_Mso100Handle, 
				 int i_i_ConnectionMode,	// COM_USB or COM_RS232
				 char *i_c_StrDevice,	// Serial port device /dev/ttyS0
				 int i_i_speed,	// Baud Rate
				 int *o_pi_IdProduct	// Return type of product
				);

int ConvertError(UC i_uc_Status);


int VerifyMatch(MORPHO_HANDLE i_h_Mso100Handle,
				PT_BUF_PK i_px_Buf_PkSrc,
				PT_BUF_PK i_px_Buf_PkRef,
				UC i_uc_NbPkRef);

int Verify(MORPHO_HANDLE i_h_Mso100Handle,
	   PT_BUF_PK i_x_Buf_Pk,
	   UC i_uc_NbFinger, UL i_ul_AsynchronousEvnt, US i_us_Timeout);


int capture( MORPHO_HANDLE		i_h_Mso100Handle,
			ULONG		AsynchronousEvnt,
			 USINT  	usTimeOut,
			 PT_EXPORT_PK	io_px_ExportPk,
			 UCHAR 		PkFormat,
			 PT_EXPORT_IMAGE io_px_ExportImage,
			ULONG	nbFingers);

UCHAR getTemplateType();
void show_banner(void);
I CommandMenu ();
I CommandCallback (PVOID i_pv_context, I i_i_command, PVOID i_pv_param);
I getUserInput(char o_auc_buffer[INPUT_BUFFER_SIZE], const char*message);

I SaveBufIn_image (PT_BUF i_px_Buf);

UCHAR MSOconnection();
UCHAR MSORegisterAsyncILV(ULONG AsynchronousEvnt);
UCHAR MSOCloseCom();
UCHAR ucFPSCaptureTemplate(ULONG nbFingers,USINT usTimeOut,ULONG AsynchronousEvnt,UCHAR PkFormat,T_EXPORT_PK ExportPk);
UCHAR ucFPSVerifyTemplate(ULONG nbFingers,USINT usTimeOut,ULONG AsynchronousEvnt,PT_EXPORT_PK ExportPk,UCHAR PkFormat);
UCHAR ucFPSVerifyMatch(ULONG NbPkRef,PT_EXPORT_PK ExportPk,UCHAR PkFormat);
UCHAR ucGetFingerImage(ULONG nbFingers,USINT usTimeOut,ULONG AsynchronousEvnt,UCHAR PkFormat,T_EXPORT_IMAGE ExportImage);
UCHAR ucGetSerialNum();
UCHAR ucFPSVerifyMany(ULONG nbFingers,USINT usTimeOut,ULONG AsynchronousEvnt,PT_EXPORT_PK ExportPk,UCHAR PkFormat);
UCHAR verifyTemplateType();

