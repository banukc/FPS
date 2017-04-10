#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libMSO.h"
#include "MSO_FPS.h"
#include "Ilv_definitions.h"


UC	g_uc_ExportScore;

/***************************************************************************/
/**
* Verify function.
* Captures a live finger and checks if it matches with one of input Pks
*/
int Verify( MORPHO_HANDLE   i_h_Mso100Handle,
	    PT_BUF_PK       i_x_Buf_Pk,	    
	    UC		    i_uc_NbFinger,
	    UL              i_ul_AsynchronousEvnt,
            US              i_us_Timeout
	    		)
{
    I  		l_i_Ret;
    UC		l_uc_Status;
    UC		l_uc_MatchingResult;
    UL		l_ul_Score = 0;
    PUL		l_pul_Score = 0;	

    fprintf(stdout,"---Captures a live finger and checks if it matches with one of input Pks---\n");

    if(g_uc_ExportScore)
	l_pul_Score = &l_ul_Score;
    else
	l_pul_Score = NULL;

    l_uc_MatchingResult = 0;
    l_ul_Score = 0;
    l_uc_Status = 0;

    l_i_Ret = MSO_Bio_Verify( i_h_Mso100Handle,
                              i_us_Timeout,           //US          i_us_Timeout,
                              0,                      //US          i_us_MatchingTreshold,
                              i_uc_NbFinger,          //UC          i_uc_NbFinger,
                              i_x_Buf_Pk, 	      //PT_BUF_PK   i_x_Buf_Pk
                              i_ul_AsynchronousEvnt,  //UL          i_ul_AsynchronousEvent,
                              &l_uc_MatchingResult,   //PUC         o_puc_MatchingResult,
                              l_pul_Score,            //PUL         o_pul_score,
                              &l_uc_Status            //PUC         o_puc_ILV_Status
                            );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
        fprintf(stdout, "Verify -----> OK\n");
        fprintf(stdout, "MatchingResult=%d score=%ld\n", l_uc_MatchingResult, l_ul_Score);

        if(l_uc_MatchingResult == ILVSTS_HIT)
        {
           // fprintf(stdout, "Verify-->  Verify OK\n"); 
        }
        else
            fprintf(stdout, "Verify-->  Verify NOT OK\n");
    }
    else
    {
        fprintf(stdout, "MSO_Bio_Verify ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}



/***************************************************************************/
/*
* Verify Match function.
* Verifies if the input PkSrc matches against list of input PkRef
*/
int VerifyMatch( MORPHO_HANDLE   i_h_Mso100Handle,
	    	 PT_BUF_PK       i_px_Buf_PkSrc,	    
	    	 PT_BUF_PK       i_px_Buf_PkRef,	    
		 UC		 i_uc_NbPkRef
	       )

{	

    I  		l_i_Ret;
    UC		l_uc_Status;
    UC		l_uc_MatchingResult;
    UL		l_ul_Score = 0;
    PUL		l_pul_Score;
    UC		l_uc_ListRefIndex;

    fprintf(stdout,"---Verifies if the input PkSrc matches against list of input PkRef---\n");

    if(g_uc_ExportScore)
	l_pul_Score = &l_ul_Score;
    else
	l_pul_Score = NULL;

    l_i_Ret = MSO_Bio_VerifyMatch( i_h_Mso100Handle,
                                   1,                       //UC        i_uc_NbPkSrc (must be set to 1)
                                   i_px_Buf_PkSrc,          //PT_BUF_PK i_px_PkSrc
                                   i_uc_NbPkRef,            //UC        i_uc_NbPkRef
                                   i_px_Buf_PkRef,  	    //PT_BUF_PK i_px_PkRef
                                   5,                       //US        i_us_MatchingTreshold,
                                   &l_uc_MatchingResult,    //PUC       o_puc_MatchingResult,
                                   &l_uc_ListRefIndex,      //PUC       o_puc_ListRefIndex,
                                   l_pul_Score,             //PUL       o_pul_score,
                                   &l_uc_Status             //PUC       o_puc_ILV_Status
                                 );

    if(l_i_Ret==0 && l_uc_Status==0)
    {
        fprintf(stdout, "Verify Match -----> OK\n");
       // fprintf(stdout, "MatchingResult=%d score=%ld\n", l_uc_MatchingResult, l_ul_Score);
        if(l_uc_MatchingResult == ILVSTS_HIT)
        {
           //fprintf(stdout, "Verify Match OK--> index: %d\n", l_uc_ListRefIndex);
        }
        else
            fprintf(stdout, "Verify Match KO: Not Identified !! \n");
    }
    else
    {
        fprintf(stdout, "MSO_Bio_VerifyMatch ret=%d status=0x%02X\n", l_i_Ret, l_uc_Status);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}

/*****************************************capture******************************************/

int capture( MORPHO_HANDLE	i_h_Mso100Handle,
			 UL				i_ul_AsynchronousEvnt,
			 US				i_us_Timeout,
			 PT_EXPORT_PK	io_px_ExportPk,
			 UC 			i_uc_PkFormat,
			 PT_EXPORT_IMAGE io_px_ExportImage,
			UL	l_ul_nbFingers	 )
{


    I  		l_i_Ret;
    UC		l_uc_Status;
    T_BUF       l_x_addField[3];
    UC		l_uc_EnrollStatus;
    UL		l_ul_UserDBIndex;
    

    //fprintf(stdout,"---Captures one finger---\n");

   

    l_i_Ret = MSO_Bio_Enroll( i_h_Mso100Handle,
                              0,                        //UC            i_uc_IndexDB,
                              i_us_Timeout,             //US            i_us_Timeout,
                              1,                        //UC            i_uc_EnrollmentType,
                             l_ul_nbFingers,                        //UC            i_uc_NbFinger,
                              0,                        //UC            i_uc_SaveRecord,
                              i_uc_PkFormat,            //UC            i_uc_NormalizedPK_Type,
                              0,                        //UC            i_uc_NbAddField,
                              (PT_BUF)&l_x_addField,    //PT_BUF        i_px_AddField,
                              i_ul_AsynchronousEvnt,    //UL			i_ul_AsynchronousEvnt,
                              io_px_ExportPk,    		//PT_EXPORT_PK  io_px_ExportPk,      //can be NULL
                              io_px_ExportImage,        //PT_EXPORT_IMAGE io_px_ExportImage, //can be NULL
                              &l_uc_EnrollStatus,       //PUC           o_puc_EnrollStatus,
                              &l_ul_UserDBIndex,        //PUL           o_pul_UserDBIndex,
                              &l_uc_Status              //PUC           o_puc_ILV_Status
                             );
    if(l_i_Ret==0 && l_uc_Status==0)
    {
        fprintf(stdout, "Capture -----> OK\n");
    }
    else
    {
        fprintf(stdout, "MSO_Bio_Enroll ret=%d status=0x%02X EnrollStatus=%d\n",
                                               l_i_Ret, l_uc_Status, l_uc_EnrollStatus);
        if(l_uc_Status != 0)
            ConvertError(l_uc_Status);
        l_i_Ret = -1;
    }

    return l_i_Ret;
}
