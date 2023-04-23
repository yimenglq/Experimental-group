#include<Windows.h>
#include<WinUser.h>
#include<stdio.h>
#include<Winsock.h>
#include<malloc.h>

#include<Shellapi.h>
#include<process.h>
#include<locale.h>

#include <vector>

#pragma comment(lib,"ws2_32.lib")









#ifndef WndProc 
#define WndProc 
#define BN_FILE 100

typedef struct _PNG_CRC
{
	DWORD CRC;

} _PNG_CRC, * _PPNG_CRC;

typedef struct _IHDR//
{
	DWORD Width;//图像高度
	DWORD Height;//图像宽度
	BYTE depth;//图像深度
	BYTE ColorType;//颜色类型
	BYTE Comperss_method;//压缩方法
	BYTE Filter_method;//滤波器方法
	BYTE Interlace_method;//隔行扫描法
	BYTE CRC[4];//CRC校验 //F97DAA93
} _IHDR,*_PIHDR ;



typedef	struct _PNG//1
{
	LONGLONG _PNG_T;//8字节PNG署名//89504E470D0A1A0A
	DWORD _PNG_IHDR_SIZE;//IHDR_SIZE
	DWORD _PNG_IHDR;//IHDR//49484452
	_IHDR _PNG_Chunk_Data;//可变长度数据
	

	//DWORD CRC;
	//_PNG_CRC CRC;//CRC校验 //F97DAA93

} img_PNG,*pimg_PNG;

typedef struct _PNG_RGB
{
	DWORD RGB_Size;
	DWORD RGB_Type;
	BYTE*  RGB_date;
	_PNG_CRC CRC;
} _PNG_RGB, * _PPNG_RGB;


typedef struct _PNG_PLTE
{
	BYTE Red;
	BYTE Green;
	BYTE Blue;

} _PNG_PLTE, * _PPNG_PLTE;




typedef struct _PNGIFO
{
	img_PNG img_PNG;
	_PNG_PLTE _PNG_COLOR[1];
} _PNGIFO,*_PPNGIFO;

typedef struct _PNG_pHYs
{
	DWORD _PNG_pHYs_Size;
	DWORD pHYs;
	DWORD wh;//水平、垂直方向上的物理分辨率（像素密度）均为3780像素/米
	BYTE m;
	_PNG_CRC CRC;

} _PNG_pHYs, * _PPN_pHYs;


typedef struct _PNG_IDAT
{
	DWORD _PNG_IDAT_Size;
	DWORD _PNG_IDAT_Type;
	BYTE* Png_Idat_Date;
	
	_PNG_CRC CRC;

} _PNG_IDAT, * _PPNG_IDAT;

typedef struct _PNG_IEND
{
	DWORD _PNG_IEND_Size;
	DWORD _PNG_IEND_Type;
	_PNG_CRC CRC;

} _PNG_IEND, * _PPNG_IEND;



/*typedef struct cd
{
	DWORD f;


} cd0, * pcd0;
typedef struct c
{
	BYTE* f;
	cd0 d;

} c0, * pc0;*/




int openFileName(HWND hwnd, OPENFILENAME* ofn, TCHAR szFilter[], TCHAR szFileName[], TCHAR szTitleName[]);
void size_BTYE(BYTE* bt, BYTE* p);
void wh_BTYE(DWORD* , DWORD* );
void ShowIHDR(img_PNG* png);

TCHAR szAppName[] = TEXT("Dib"),szAPPpoupName []=TEXT("poup");



LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static BITMAPINFO *pbmif, *pbmif_1;
	static BYTE* pBit;
	static int cxDib, cyDib, cBits,cx,cy;
	static OPENFILENAME ofn;
	static TCHAR szFileName[MAX_PATH], szTitleName[MAX_PATH];
	static TCHAR szFilter[] = TEXT("Dib (*.BMP)\0*.bmp\0")TEXT("ALL (*.*)\0*.*\0")TEXT("?>?KK(*.cnk)\0*.cnk\0\0");
	static TCHAR bt[] = TEXT("button"),edit[]= TEXT("edit");
	static HWND btWnd,editWnd,h;
	//static	BITMAPINFO pbmif_1 = {0};
	static BITMAPFILEHEADER *pbmfh,*pbmfh_Bit;//DIB文件头结构体
	static _PNG_IDAT* _Png_Idat[1];//IDAT每一个保存
	static int _Png_Idat_Size = 0;//IDAT的引索

	static HBITMAP hbmp;


	static	HINSTANCE hInstance;
	DWORD dwBytesRead,dwHighSize,dwFileSize;
	HANDLE hFile;
	HDC hdc;
	HMENU menu;
	
	PAINTSTRUCT ps;//WM_PINT消息中使用  取得HDC

	BOOL bSuccess;


	switch (message)
	{
	case WM_CREATE:
//(HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE) 
		
		hInstance = ((LPCREATESTRUCT)lParam)->hInstance;

		openFileName(hwnd, &ofn, szFilter, szFileName, szTitleName);
		LOWORD(GetDialogBaseUnits());
	btWnd = CreateWindow(bt, NULL,
			WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
			0, 0,
		LOWORD(GetDialogBaseUnits())*4, HIWORD(GetDialogBaseUnits())*2,
			hwnd, (HMENU)1,((LPCREATESTRUCT)lParam)->hInstance,NULL
		);

		
	//ShowWindow(h, SW_SHOW);

	SetWindowText(btWnd, TEXT("点我"));
	{
		RECT rt;
		GetClientRect(hwnd, &rt);
		MoveWindow(btWnd, rt.right/2, rt.bottom/2, LOWORD(GetDialogBaseUnits()) * 4, HIWORD(GetDialogBaseUnits()) * 2,
			TRUE);

	}

		
	
		return 0;

	case WM_SIZE:
	{
		SetFocus(hwnd);
		RECT rt = { 0 };
		cx = rt.right = LOWORD(lParam);
		cy = rt.bottom = HIWORD(lParam);
		MoveWindow(btWnd, rt.right / 2, rt.bottom / 2, LOWORD(GetDialogBaseUnits()) * 4, HIWORD(GetDialogBaseUnits()) * 2,
			TRUE);

	}
		return 0;

	case WM_KEYDOWN:

		if (wParam == 0x42)
		{	
			
			//_beginthread()
			h = CreateWindow(
				szAPPpoupName, NULL,
				WS_CHILD | WS_VISIBLE | WS_SIZEBOX | WS_BORDER,
				1, 10, 100, 300, hwnd, (HMENU)100, hInstance,//(HINSTANCE) GetWindowLong(hwnd, GWLP_HINSTANCE),
				NULL
			);
			 

			
			
			

		}if (wParam == 'V')
			{
				SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_ACCEPTFILES);
				SetWindowPos(hwnd, HWND_TOP, 0, 0, 500, 600, SWP_DRAWFRAME);
			}
		


		return 0;


	case WM_DROPFILES:
	{
		static	TCHAR filePath[256] = { 0 };
		FILE *f;
		LONGLONG i = 0;
		if (pbmfh)
		{
			free(pbmfh);
			pbmfh = NULL;
			pbmif = NULL;
			pBit = NULL;
		}

			
		DragQueryFile((HDROP)wParam, 0, filePath, 256);
		

		if (!_wfopen_s(&f, filePath, L"rb"))//二进制读取文件
		{
			
			_fseeki64(f, 0L, SEEK_END);//文件指针移动到二进制文件流末尾
			i = _ftelli64(f);//返回当前文件指针所在位置  从头到当前 (字节为单位)
			pbmfh = (BITMAPFILEHEADER*) malloc(i);
			rewind(f);//将文件指针放置到文件流头部
			fread_s(pbmfh, i, i, 1, f);//读取二进制文件  fwrite二进制写入
			
			pbmif = (BITMAPINFO*)(pbmfh + 1);
			pBit = (BYTE*)pbmfh + pbmfh->bfOffBits;
			cxDib = pbmif->bmiHeader.biWidth;
			cyDib = pbmif->bmiHeader.biHeight;
		}
			

		PostMessage(hwnd, WM_COMMAND, MAKEWPARAM( 0,BN_FILE), (LPARAM)&filePath);
		InvalidateRect(hwnd, NULL, TRUE);
		UpdateWindow(hwnd);
	}
	return 0;



	case WM_COMMAND://子窗口发送给父窗口的消息
		//HIWORD(wParam) 通知码
		//LOWORD(wParam) 窗口ID(创建时的MENU)
		//lParam  窗口句柄
		switch (HIWORD(wParam))//低位字节通知码
		{
		case BN_FILE:
		{	
			FILE* f;
			WCHAR* str = (WCHAR*)lParam;
			setlocale(LC_ALL, "en_US.UTF-8");//设置或读取地域化信息。
			errno_t err;
			err = fopen_s(&f, "c.name", "a+");
				//err = fopen_s(&f, "c.name", "w+");


			//fseek(f, 0L, SEEK_END);
			 
			 int rc = fputws(str, f);
			 fputws(L"\n\n\n\t发发\n", f);
			 if (rc == EOF)
				printf("fputws()"); // POSIX requires that errno is set
			//err = fputws(	str, f);
			fclose(f);

		}
			return 0;;

		case BN_CLICKED:
			if (!GetOpenFileName(&ofn))
				return 0;
			if (pbmfh)
			{
				free(pbmfh);
				pbmfh = NULL;
			}
			if(pbmif)
			{
				
				pbmif = NULL;
			}
			if(pBit)
			{
				free(pBit);
				pBit = NULL;
			}
			if (pbmif_1)
			{
				free(pbmif_1);
				pbmif_1 = NULL;
			}
			if (_Png_Idat[0])
			{
				free(_Png_Idat[0]);
				_Png_Idat[0] = NULL;
				_Png_Idat_Size = 0;
			}
			if (pbmfh_Bit)
			{
				free(pbmfh_Bit);
				pbmfh_Bit = NULL;
			}






			InvalidateRect((HWND)GetWindowLong(hwnd, GWLP_HWNDPARENT), NULL, TRUE);
			UpdateWindow((HWND)GetWindowLong(hwnd, GWLP_HWNDPARENT));

			//打开文件
			if (INVALID_HANDLE_VALUE == (hFile = CreateFile(ofn.lpstrFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
				FILE_FLAG_SEQUENTIAL_SCAN, NULL)))
			{
				MessageBox((HWND)GetWindowLong(hwnd, GWLP_HWNDPARENT), TEXT("失败"), TEXT("打开文件失败"), MB_OK | MB_ICONERROR);
				return 0;
			}

			 dwFileSize = GetFileSize(hFile, &dwHighSize);
			 
			 pbmfh =(BITMAPFILEHEADER*)malloc(dwFileSize);

			 

			bSuccess = ReadFile(hFile, pbmfh, dwFileSize, &dwBytesRead,NULL);
			if (!bSuccess)
			{
				MessageBox(NULL, TEXT("失败"), TEXT("读取失败"), MB_OK | MB_ICONERROR);
				CloseHandle(hFile);
				return 0;
			}


			

			//BMP
			if ((pbmfh->bfType != * (WORD*)"BM" || pbmfh->bfType != 0x4D42) || pbmfh->bfSize != dwFileSize)
			{
				//PNG
				if (((img_PNG*)pbmfh)->_PNG_T & 0x89504E470D0A1A0A)
				{
					/*BYTE c[4];


					for (int i =0;i<4 ;i++)
					{
						c[i] = *(((BYTE*)& crc->_PNG_IHDR_SIZE)+i);
					}*/

					pbmfh_Bit = (BITMAPFILEHEADER*)malloc(dwFileSize);//临时储存字节


					
					img_PNG* crc = ((img_PNG*)pbmfh);

					
					BYTE c[sizeof(crc->_PNG_IHDR_SIZE)] = { 0 };
					int ci = sizeof(crc->_PNG_IHDR_SIZE);
					for (int o = 0; o < ci; o++)
					{
						c[o] = *((BYTE*)&crc->_PNG_IHDR_SIZE + ci - 1 - o);
					}
					((img_PNG*)pbmfh_Bit)->_PNG_Chunk_Data = crc->_PNG_Chunk_Data;

					((img_PNG*)pbmfh_Bit)->_PNG_IHDR_SIZE = *(DWORD*)c;

					wh_BTYE((DWORD*)&(((img_PNG*)pbmfh_Bit)->_PNG_Chunk_Data.Width), &(crc->_PNG_Chunk_Data.Width));
					wh_BTYE((DWORD*)&(((img_PNG*)pbmfh_Bit)->_PNG_Chunk_Data.Height), &(crc->_PNG_Chunk_Data.Height));

					ShowIHDR((img_PNG*)pbmfh_Bit);


					int a = sizeof(*crc);


					pbmif = (BITMAPINFO*)((pimg_PNG)((BYTE*)crc + 33));
					

					TCHAR xs[] = {
						TEXT("bKGD cHRM gAMA hIST iCCP iTXt pHYs sBIT sPLT sRGB tEXt tIME tRNS zTXt")
					};
					_PNG_RGB* p = NULL;
					p = (_PNG_RGB*)pbmif;
					
					_PNG_RGB pngRGB = {0};
					
					

					while (true)
					{
						pngRGB = * p;
						pngRGB.RGB_date = (BYTE*)p + 4 + 4;
						
							

						//BYTE l = *(p->RGB_date);
						
						size_BTYE((BYTE*)&pngRGB, (BYTE*)p);
						
						for (int i = 0; i < sizeof(DWORD); i++)
							*((BYTE*)&(pngRGB.CRC) + i) = *((pngRGB.RGB_date) + pngRGB.RGB_Size + i);
						/*BYTE c[sizeof(((_PNG_RGB*)pbmif)->RGB_Size)] = { 0 };
						int ci = sizeof(((_PNG_RGB*)pbmif)->RGB_Size);
						for (int o = 0; o < ci; o++)
						{
							c[o] = *((BYTE*)&p->RGB_Size + ci - 1 - o);
						}

						p->RGB_Size = (DWORD) * c;*/
						if(!pbmif_1)
							pbmif_1 = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + pngRGB.RGB_Size);
						if (p->RGB_Type == *(DWORD*)"IEND")
						{	static int c = 0;
							static INT64 size = 0;
							BOOL pBit_f = 0;
							//pBit = (BYTE*)malloc(sizeof(DWORD));
							if (0)
							{
							A:	pBit = (BYTE*)malloc(size);
								
								size = 0;
								c = 0;
								pBit_f = 1;
							}
							
							
							for (size_t i = 0; i < _Png_Idat_Size - 1; i++)
							{
								
								//pBit = (BYTE*)realloc(pBit, size+(_Png_Idat[0] + i)->_PNG_IDAT_Size);
								if(pBit_f)
							   for(int i_size = 1 ;  i_size <= (_Png_Idat[0] + i)->_PNG_IDAT_Size;  i_size++)
							   {
								   *(pBit + c + i_size - 1) = *((_Png_Idat[0]+i)->Png_Idat_Date + i_size - 1);
								   
							   }
							   c += (_Png_Idat[0] + i)->_PNG_IDAT_Size;
							   size += (_Png_Idat[0] + i)->_PNG_IDAT_Size;
							   
							}
							if (!pBit_f)
							{
								goto A;

							}

							//free(pbmfh);
							p = NULL;
							return 0;
						}

						if (p->RGB_Type == *(DWORD*)"PLTE")
						{
							BYTE* bt;
							bt = (BYTE*)pbmif_1->bmiColors;
							int prs = pngRGB.RGB_Size;

							while (prs)
							{
								*bt = *(pngRGB.RGB_date + prs - 1);
								prs--;
							}
							break;
						}
							
						if (p->RGB_Type == *(DWORD*)"sRGB")
						{
							
							//pbmif->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); // top-down image 
							//pbmif->bmiHeader.biPlanes = 1;
							//pbmif->bmiHeader.biBitCount = 0;
							//pbmif->bmiHeader.biCompression = BI_PNG;
							//pbmif->bmiColors = (p->RGB_date);
							//p->RGB_date = (BYTE*)pbmif_1.bmiColors;

							
							/*pbmif_1 = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + pngRGB.RGB_Size);*/
							
							BYTE* bt;
							bt = (BYTE*)pbmif_1->bmiColors;
							int prs = pngRGB.RGB_Size;

							while (prs)
							{
								*bt = *(pngRGB.RGB_date + prs-1);
								prs--;
							}
							//_memccpy(pbmif_1->bmiColors, p->RGB_date, NULL, p->RGB_Size);
							//pbmif_1->bmiColors[0] = *(RGBQUAD*)(p->RGB_date);
						}
						if (p->RGB_Type == *(DWORD*)"IDAT")
						{
							cxDib = (((img_PNG*)pbmfh_Bit)->_PNG_Chunk_Data.Width);
							cyDib = (((img_PNG*)pbmfh_Bit)->_PNG_Chunk_Data.Height);
							pbmif_1->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
							pbmif_1->bmiHeader.biPlanes = 1;
							pbmif_1->bmiHeader.biBitCount = 2;//((img_PNG*)pbmfh)->_PNG_Chunk_Data.ColorType;
							pbmif_1->bmiHeader.biCompression = BI_RGB;
							pbmif_1->bmiHeader.biWidth = cxDib;
							pbmif_1->bmiHeader.biHeight = cyDib;
							pbmif_1->bmiHeader.biSizeImage = pngRGB.RGB_Size;
							pbmif->bmiHeader.biClrUsed = 0;
							//pBit = pngRGB.RGB_date;
							pbmif = pbmif_1;
							

							

							if(!_Png_Idat[0])
								_Png_Idat[0] =  (_PNG_IDAT*)malloc(sizeof(_PNG_IDAT)*MAX_PATH) ;
						
						//	
						//	//_PNG_RGB  = { 0 };
							_Png_Idat[0][_Png_Idat_Size]._PNG_IDAT_Size = pngRGB.RGB_Size;
							_Png_Idat[0][_Png_Idat_Size]._PNG_IDAT_Type = pngRGB.RGB_Type;
							_Png_Idat[0][_Png_Idat_Size].Png_Idat_Date = pngRGB.RGB_date;
							_Png_Idat[0][_Png_Idat_Size].CRC = pngRGB.CRC;
							_Png_Idat_Size++;



						
						}
						//pBit = (BYTE*)_Png_Idat[0];

						
						

						p = (_PPNG_RGB)((BYTE*)p+pngRGB.RGB_Size+4+4+4);
						
						
					}


					


					

				}
				else
				{
					MessageBox(NULL, TEXT("失败"), TEXT("文件不是BM,不是Dib图"), MB_OK | MB_ICONERROR);
					CloseHandle(hFile);
					return 0;
				}
				
			}
			
			pbmif = (BITMAPINFO*)(pbmfh + 1);
			pBit =(BYTE*)pbmfh +pbmfh->bfOffBits;//到像素位的偏移量

			 hbmp = CreateDIBSection(NULL, pbmif, 0, (void**)&pBit, NULL, 0);
			 memcpy(pBit, (BYTE*)pbmfh + pbmfh->bfOffBits,
				 ((((BITMAPINFO*)(pbmfh + 1))->bmiHeader.biWidth*
					 ((BITMAPINFO*)(pbmfh + 1))->bmiHeader.biBitCount + 31) >> 3) * (((BITMAPINFO*)(pbmfh + 1))->bmiHeader.biHeight-1)

			 );

			if (pbmif->bmiHeader.biSize == sizeof(BITMAPCOREHEADER))
			{
				cxDib = ((BITMAPCOREHEADER*)pbmif)->bcWidth;
				cyDib = ((BITMAPCOREHEADER*)pbmif)->bcHeight;
			}
			else 
			{
				cxDib = pbmif->bmiHeader.biWidth;
				cyDib = pbmif->bmiHeader.biHeight;

			}
			







		/*	editWnd = CreateWindow(TEXT("edit"), NULL,
		ES_AUTOVSCROLL | WS_CHILD | WS_VISIBLE | WS_VSCROLL|  WS_BORDER | ES_MULTILINE,
		0, 0, cx/2, cy/2, hwnd, (HMENU)2,(HINSTANCE)GetWindowLong(hwnd, GWLP_HINSTANCE) , NULL
		);
			 pbmfh->bfType;
			SendMessage(editWnd, EM_REPLACESEL, TRUE,0);*/


		InvalidateRect(hwnd, NULL, TRUE);
			break;

		case EN_ERRSPACE:
			MessageBeep(0);
			break;

			
		}
		return 0;

	case WM_PAINT:
		
		hdc = BeginPaint(hwnd, &ps);
		
		if (pbmif)
		{
			 
			SetDIBitsToDevice(hdc,
				30, 30, cxDib, cyDib, 0, 0, 0, cyDib, pBit, pbmif, DIB_RGB_COLORS);
				
			StretchDIBits(hdc, cxDib / 10+10, 0, cxDib/5, cyDib/5, 0, 0, cxDib, cyDib, pBit, pbmif, DIB_RGB_COLORS, SRCCOPY);
			
			//goto P;
		
			HDC hdc_C = CreateCompatibleDC(hdc);
			SelectObject(hdc_C, hbmp);

			int mod =  SetStretchBltMode(hdc, HALFTONE);

			StretchBlt(hdc, cxDib / 10, (cyDib / 5), cxDib / 5, cyDib / 5, hdc_C, 0, 0, cxDib, cyDib, SRCCOPY);
			//BitBlt(hdc, 0, 0, cxDib / 10, cyDib / 10, hdc_C, 0, 0, SRCCOPY);

			DeleteDC(hdc_C);
			goto P;
		
			if (hdc)
			{
				HDC hdc_C = CreateCompatibleDC(hdc);
				SelectObject(hdc_C, hbmp);
				
				//SetMapMode(hdc_C, MM_ISOTROPIC);
				//SetMapMode 函数设置指定设备上下文的映射模式。 映射模式定义用于将页空间单位转换为设备空间单位的度量单位，并定义设备的 x 轴和 y 轴的方向。
				
				
				//SetWindowExtEx(hdc, cxDib, cyDib, NULL);
				//SetWindowExtExtEx 函数使用指定值设置设备上下文窗口的水平和垂直范围。
				//SetViewportExtEx();
				//SetViewportExtEx 函数使用指定的值为设备上下文设置视区的水平和垂直范围。
				//SetViewportOrgEx();
				//SetViewportOrgEx 函数指定哪个设备点映射到窗口原点 (0，0) 。

				//SetStretchBltMode(hdc, HALFTONE);
				
				POINT pt;
				//SetBrushOrgEx(hdc_C, 0, 0, &pt);
				StretchBlt(hdc, 0, 0, cxDib / 10, cyDib / 10, hdc_C, 0, 0, cxDib, cyDib, SRCCOPY);
				//BitBlt(hdc, 0, 0, cxDib / 10, cyDib / 10, hdc_C, 0, 0, SRCCOPY);
				
				DeleteDC(hdc_C);
			}
			
			
		}

		P:EndPaint(hwnd, &ps);


		return 0;

	case WM_DESTROY://
		PostQuitMessage(0);
		return 0;

	default:
		break;

	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}


int showTextFileName(HWND hwnd,OPENFILENAME* ofn)
{
	
	

	
	return 0;
}


int openFileName(HWND hwnd,OPENFILENAME* ofn, TCHAR szFilter[] , TCHAR szFileName[], TCHAR szTitleName[])
{
	ofn->lStructSize = sizeof(OPENFILENAME);
	ofn->hwndOwner = hwnd;
	ofn->hInstance = NULL;
	ofn->lpstrFilter = szFilter;
	ofn->lpstrCustomFilter = NULL;
	ofn->nMaxCustFilter = 0;
	ofn->nFilterIndex = 0;
	ofn->lpstrFile = szFileName;
	ofn->nMaxFile = MAX_PATH;
	ofn->lpstrFileTitle = szTitleName;
	ofn->nMaxFileTitle = MAX_PATH;
	ofn->lpstrInitialDir = NULL;
	ofn->lpstrTitle = NULL;
	ofn->Flags = 0;
	ofn->nFileOffset = 0;
	ofn->nFileExtension = 0;
	ofn->lpstrDefExt = TEXT("BMP");
	ofn->lCustData = 0;
	ofn->lpfnHook = NULL;
	ofn->lpTemplateName = NULL;
	return 0;
}


void size_BTYE(BYTE* bt,BYTE* p)
{
	BYTE c[sizeof(((_PNG_RGB*)bt)->RGB_Size)] = { 0 };
	int ci = sizeof(((_PNG_RGB*)bt)->RGB_Size);
	for (int o = 0; o < ci; o++)
	{
		c[o] = *((BYTE*)&((_PNG_RGB*)p)->RGB_Size + ci - 1 - o);
	}
	DWORD d = ntohl(((_PNG_RGB*)p)->RGB_Size);// LOWORD(* (DWORD*)c);
	//((_PNG_RGB*)bt)->RGB_Size = LOWORD(*(DWORD*)c);
	((_PNG_RGB*)bt)->RGB_Size = d;
	//((_PNG_RGB*)p)->RGB_Size = *(DWORD*)c;

}

void wh_BTYE(DWORD* drc,DWORD* src)
{
	
	BYTE c[sizeof(DWORD)] = { 0 };
	int ci = sizeof(DWORD);
	for (int o = 0; o < ci; o++)
	{
		c[o] = *((BYTE*)src + ci - 1 - o);
	}

	*drc = *(DWORD*)c;
	BYTE m = *c;


	//c0* d = (c0*)crc;
}
void ShowIHDR(img_PNG* png )
{
	png->_PNG_Chunk_Data;
	
}


LRESULT CALLBACK wndProcPOUP(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	default:
		
		break;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}


#endif
