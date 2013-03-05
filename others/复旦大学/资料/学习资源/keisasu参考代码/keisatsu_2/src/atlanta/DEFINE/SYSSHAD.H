/*	By Y.Suzuki 1996/10/15	*/
/* Original File : jun\usr2:\src\ichou\define\sysshad.h */
#ifndef sysshad_h
	#define sysshad_h

/************************************************************************
 * シェーディング領域													*
 * 1993/11/27															*
 * 吉川弘康																*
 ************************************************************************/
#define SYS_INITIAL_MAX		192
#if (PRO_IMAGE_PROCESSOR == IMAGE_PROCESSOR_LC82103)
	#define SYS_SHADING_MAX		2048
#else
	#define SYS_SHADING_MAX		224
#endif

#endif
