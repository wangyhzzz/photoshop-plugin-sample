// ADOBE SYSTEMS INCORPORATED
// Copyright  1993 - 2002 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this 
// file in accordance with the terms of the Adobe license agreement
// accompanying it.  If you have received this file from a source
// other than Adobe, then your use, modification, or distribution
// of it requires the prior written permission of Adobe.
//-------------------------------------------------------------------
//-------------------------------------------------------------------------------
//
//	File:
//		FileUtilitiesMac.cpp
//
//	Description:
//		This library contains sources and functions
//		to simplify the use of extremely common file
//		functions for plug-ins. 
//
//	Use:
//		Macintosh routines with common names. 
//
//-------------------------------------------------------------------------------

#include "PIDefines.h"
#include "FileUtilities.h"
#if __PIMac__
#include <Cocoa/Cocoa.h>
#endif

/*****************************************************************************/
// On the mac the savePanel opened it up, just check that we have something
// See DoUI for Outbound example on mac
Boolean PIOpenFile (FileHandle fRefNum)
{
    if (fRefNum)
        return  TRUE;
	return FALSE;
}

/*****************************************************************************/

Boolean PICloseFileAndMakeAlias (FileHandle fRefNum, NSString * filename,
					             Boolean *dirty, PIPlatformFileHandle *alias)
{
    
    [fRefNum closeFile];

    fRefNum = nil;

    if (dirty)
        *dirty = FALSE;
    
    if (alias && filename)
    {
        *alias = nil;
        CFURLRef fileURL = (CFURLRef)[[NSURL alloc] initFileURLWithPath:filename isDirectory:FALSE];
        filename = nil;
        if (fileURL)
        {
    
            FSRef	fsRef;
    
            if (CFURLGetFSRef(fileURL, &fsRef))
            {
                AliasHandle	temp;
                OSErr	error = FSNewAliasMinimal(&fsRef, &temp);
                if (error == noErr)
                {
                    *alias = temp;
                    CFRelease(fileURL);
                    return TRUE;
                }
            }
        
            CFRelease(fileURL);
        
        }
    }
    
	return FALSE;
    
}

/*****************************************************************************/

OSErr PSSDKWrite(FileHandle refNum, int32 * count, void * buffPtr)
{
    if (count == NULL || buffPtr == NULL || *count <= 0)
        return writErr;
    unsigned long long cPos = [refNum offsetInFile];
    NSData * nsData = [NSData dataWithBytes:buffPtr length:*count];
    [refNum writeData:nsData];
    unsigned long long nPos = [refNum offsetInFile];
    if (*count != (nPos - cPos))
        return writErr;
    return 0;
}

/*****************************************************************************/

OSErr PSSDKWrite(int32 refNum, int32 * count, void * buffPtr)
{
    if (NULL == count || NULL == buffPtr)
        return writErr;
    
    ByteCount bytes = *count;
    
    ByteCount bCount = *count;
    
    OSErr err = FSWriteFork(refNum, fsAtMark | noCacheMask, 0, bytes, buffPtr, &bCount);
    
    if (noErr != err)
        return err;
    
    if (bytes != bCount)
        return writErr;
    
    *count = bCount;
    
    return err;
    
}

/*****************************************************************************/

OSErr PSSDKSetFPos(int32 refNum, short posMode, long posOff)
{
	OSErr err = FSSetForkPosition(refNum, posMode, posOff);
	return err;
}

/*****************************************************************************/

OSErr PSSDKRead(int32 refNum, int32 * count, void * buffPtr)
{
	if (NULL == count || NULL == buffPtr)
		return writErr;

	ByteCount bytes = *count;

	ByteCount bCount = *count;

	OSErr err = FSReadFork(refNum, fsAtMark, 0, bytes, buffPtr, &bCount);

	if (bytes != bCount)
		return readErr;
		
	*count = bCount;

	return err;
}

// end FileUtilitiesMac.cpp
