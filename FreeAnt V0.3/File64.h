//////////////////////////////////////
// File64.h : header file

#ifndef _FILE64_H_
#define _FILE64_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFile64 : public CFile
{
public:
	// Constructors
	CFile64();
	CFile64(int hFile);
	CFile64(LPCTSTR lpszFileName, UINT nOpenFlags);
	// Attributes
	ULONGLONG GetPosition();
	
	// Overridables
	virtual ULONGLONG Seek(LONGLONG lOff, UINT nFrom);
	virtual void SetLength(ULONGLONG dwNewLen);
	ULONGLONG GetLength();
	virtual void LockRange(ULONGLONG dwPos, ULONGLONG dwCount);
	virtual void UnlockRange(ULONGLONG dwPos, ULONGLONG dwCount);
};

#endif //#define _FILE64_H_