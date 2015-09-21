#include "dump_bmp.h"

#define     HAL_PIXEL_FORMAT_RGBA_8888     1
#define     HAL_PIXEL_FORMAT_RGBX_8888     2
#define     HAL_PIXEL_FORMAT_RGB_888       3
#define     HAL_PIXEL_FORMAT_RGB_565       4
#define     HAL_PIXEL_FORMAT_BGRA_8888     5
#define     HAL_PIXEL_FORMAT_RGBA_5551     6
#define     HAL_PIXEL_FORMAT_RGBA_4444     7
#define     HAL_PIXEL_FORMAT_YCbCr_422_SP  0x10
#define     HAL_PIXEL_FORMAT_YCbCr_420_SP  0x11
#define     HAL_PIXEL_FORMAT_YCbCr_422_P   0x12
#define     HAL_PIXEL_FORMAT_YCbCr_420_P   0x13
#define     HAL_PIXEL_FORMAT_YCbCr_422_I   0x14
#define     HAL_PIXEL_FORMAT_YCbCr_420_I   0x15
#define     HAL_PIXEL_FORMAT_CbYCrY_422_I  0x16
#define     HAL_PIXEL_FORMAT_CbYCrY_420_I  0x17

//static char valuePath[PROPERTY_VALUE_MAX];

int dump_bmp(const char* filename, void* buffer_addr, unsigned int buffer_format, unsigned int buffer_width, unsigned int buffer_height)
{
    FILE* fp;
    WORD bfType;
    BITMAPINFO bmInfo;
    RGBQUAD quad;
    int ret = 0;
    fp = fopen(filename, "wb");
    if(!fp)
    {
        ret = -1;
        goto fail_open;
    }
    bfType = 0x4D42;

    memset(&bmInfo, 0, sizeof(BITMAPINFO));

    bmInfo.bmfHeader.bfOffBits = sizeof(WORD) + sizeof(BITMAPINFO);
    bmInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmInfo.bmiHeader.biWidth = buffer_width;
    bmInfo.bmiHeader.biHeight = -buffer_height;
    bmInfo.bmiHeader.biPlanes = 1;

    
    
    if(buffer_format ==  HAL_PIXEL_FORMAT_RGB_565) {
        bmInfo.bmfHeader.bfOffBits += 4*sizeof(U32);
        bmInfo.bmiHeader.biBitCount = 16;
        bmInfo.bmiHeader.biCompression = BI_BITFIELDS;
        quad.rgbRedMask      = 0x001F;
        quad.rgbGreenMask    = 0x07E0;
        quad.rgbBlueMask     = 0xF800;
        quad.rgbReservedMask = 0;
        bmInfo.bmiHeader.biSizeImage = buffer_width * buffer_height * sizeof(U16);
        }

    else if(buffer_format == HAL_PIXEL_FORMAT_RGBA_8888) {
        bmInfo.bmfHeader.bfOffBits += 4*sizeof(U32);
        bmInfo.bmiHeader.biBitCount = 32;
        bmInfo.bmiHeader.biCompression = BI_BITFIELDS;
        quad.rgbRedMask      = 0x00FF0000;
        quad.rgbGreenMask    = 0x0000FF00;
        quad.rgbBlueMask     = 0x000000FF;
        quad.rgbReservedMask = 0xFF000000;
        bmInfo.bmiHeader.biSizeImage = buffer_width * buffer_height * sizeof(U32);
        }
    else if(buffer_format ==HAL_PIXEL_FORMAT_RGBX_8888) {/*not sure need investigation*/
        bmInfo.bmfHeader.bfOffBits += 4*sizeof(U32);
        bmInfo.bmiHeader.biBitCount = 32;
        bmInfo.bmiHeader.biCompression = BI_BITFIELDS;
        quad.rgbRedMask      = 0x00FF0000;
        quad.rgbGreenMask    = 0x0000FF00;
        quad.rgbBlueMask     = 0x000000FF;
        quad.rgbReservedMask = 0x00000000;
        bmInfo.bmiHeader.biSizeImage = buffer_width * buffer_height * sizeof(U32);
        }
    else if(buffer_format == HAL_PIXEL_FORMAT_BGRA_8888) {/*not sure need investigation*/
        bmInfo.bmfHeader.bfOffBits += 4*sizeof(U32);
        bmInfo.bmiHeader.biBitCount = 32;
        bmInfo.bmiHeader.biCompression = BI_BITFIELDS;
        quad.rgbRedMask      = 0x000000FF;
        quad.rgbGreenMask    = 0x0000FF00;
        quad.rgbBlueMask     = 0x00FF0000;
        quad.rgbReservedMask = 0xFF000000;
        bmInfo.bmiHeader.biSizeImage = buffer_width * buffer_height * sizeof(U32);
        }
    else if(buffer_format == HAL_PIXEL_FORMAT_RGB_888) {/*not sure need investigation*/
        bmInfo.bmfHeader.bfOffBits += 4*sizeof(U32);
        bmInfo.bmiHeader.biBitCount = 24;
        bmInfo.bmiHeader.biCompression = BI_BITFIELDS;
        quad.rgbRedMask      = 0x000000FF;
        quad.rgbGreenMask    = 0x0000FF00;
        quad.rgbBlueMask     = 0x00FF0000;
        quad.rgbReservedMask = 0x00000000;
        bmInfo.bmiHeader.biSizeImage = buffer_width * buffer_height * sizeof(U8) * 3;
        }
    else if(buffer_format == HAL_PIXEL_FORMAT_RGBA_5551) { /*not sure need investigation*/
        bmInfo.bmfHeader.bfOffBits += 4*sizeof(U32);
        bmInfo.bmiHeader.biBitCount = 16;
        bmInfo.bmiHeader.biCompression = BI_BITFIELDS;
        quad.rgbRedMask      = 0x000000FF;
        quad.rgbGreenMask    = 0x0000FF00;
        quad.rgbBlueMask     = 0x00FF0000;
        quad.rgbReservedMask = 0x00000000;
        bmInfo.bmiHeader.biSizeImage = buffer_width * buffer_height * sizeof(U8) * 2;
        }
    else if(buffer_format == HAL_PIXEL_FORMAT_RGBA_4444) {/*not sure need investigation*/
        bmInfo.bmfHeader.bfOffBits += 4*sizeof(U32);
        bmInfo.bmiHeader.biBitCount = 16;
        bmInfo.bmiHeader.biCompression = BI_BITFIELDS;
        quad.rgbRedMask      = 0x000000FF;
        quad.rgbGreenMask    = 0x0000FF00;
        quad.rgbBlueMask     = 0x00FF0000;
        quad.rgbReservedMask = 0x00000000;
        bmInfo.bmiHeader.biSizeImage = buffer_width * buffer_height * sizeof(U8) * 2;
        }
    else if(buffer_format == HAL_PIXEL_FORMAT_YCrCb_420_SP || buffer_format == HAL_PIXEL_FORMAT_YCbCr_420_SP || buffer_format == HAL_PIXEL_FORMAT_YCbCr_420_P || buffer_format == HAL_PIXEL_FORMAT_YV12) {
        bmInfo.bmfHeader.bfOffBits += 256*sizeof(U32);
        bmInfo.bmiHeader.biBitCount = 8;
        bmInfo.bmiHeader.biCompression = BI_RGB;
        {
            for(int i=0; i<256; i++)
            {
                quad.table[i].rgbRed      = i;
                quad.table[i].rgbGreen    = i;
                quad.table[i].rgbBlue     = i;
                quad.table[i].rgbReserved = 0;
            }
        }
        bmInfo.bmiHeader.biSizeImage = (buffer_width * buffer_height * sizeof(U8) * 3)>>1;
        }

   else {
        assert(false);
    }

    bmInfo.bmfHeader.bfSize = bmInfo.bmfHeader.bfOffBits + bmInfo.bmiHeader.biSizeImage;

    if(buffer_format == HAL_PIXEL_FORMAT_RGB_565 ||  buffer_format == HAL_PIXEL_FORMAT_RGBA_8888 || buffer_format == HAL_PIXEL_FORMAT_RGB_888 || buffer_format == HAL_PIXEL_FORMAT_BGRA_8888 || buffer_format == HAL_PIXEL_FORMAT_RGBA_5551 || buffer_format == HAL_PIXEL_FORMAT_RGBA_4444 || buffer_format == HAL_PIXEL_FORMAT_RGBX_8888) {
    
	fwrite(&bfType, sizeof(WORD), 1, fp);
        fwrite(&bmInfo, sizeof(BITMAPINFO), 1, fp);
        fwrite(&quad, 4*sizeof(U32), 1, fp);
        }
    else if(buffer_format == HAL_PIXEL_FORMAT_YCbCr_420_SP || buffer_format == HAL_PIXEL_FORMAT_YCrCb_420_SP || buffer_format == HAL_PIXEL_FORMAT_YCbCr_420_P || buffer_format == HAL_PIXEL_FORMAT_YV12) {
    
        //fwrite(&quad, 256*sizeof(U32), 1, fp);
        
    }
    fwrite(buffer_addr, bmInfo.bmiHeader.biSizeImage, 1, fp);
    fclose(fp);
    return ret;
fail_open:
    ALOGE("dump layer failed to open path is:%s" , filename);
    return ret;
}
int dump_layer(const char* path ,const char* pSrc , const char* ptype ,  int width , int height , int format ,int64_t randNum ,  int index , int LayerIndex = 0) {
    char fileName[MAX_DUMP_PATH_LENGTH + MAX_DUMP_FILENAME_LENGTH];
    
    if(format == HAL_PIXEL_FORMAT_RGBA_8888) {
		sprintf(fileName , "%s%lld_%s_%d_rgba_%dx%d_%d.bmp" ,path, randNum , ptype , LayerIndex , width, height,index);
		}
    else if(format == HAL_PIXEL_FORMAT_RGBX_8888) {
		sprintf(fileName , "%s%lld_%s_%d_rgbx_%dx%d_%d.bmp" ,path, randNum , ptype , LayerIndex , width, height,index);
		}
    else if(format ==HAL_PIXEL_FORMAT_BGRA_8888) {
		sprintf(fileName , "%s%lld_%s_%d_bgra_%dx%d_%d.bmp" ,path, randNum , ptype , LayerIndex ,width, height,index);
		}
    else if(format == HAL_PIXEL_FORMAT_RGB_888) {
		sprintf(fileName , "%s%lld_%s_%d_rgb888_%dx%d_%d.bmp" ,path, randNum , ptype , LayerIndex ,width, height,index);
		}
    else if(format == HAL_PIXEL_FORMAT_RGBA_5551) {
		sprintf(fileName , "%s%lld_%s_%d_rgba5551_%dx%d_%d.bmp" ,path, randNum , ptype , LayerIndex , width, height,index);
		}
    else if(format == HAL_PIXEL_FORMAT_RGBA_4444) {
		sprintf(fileName , "%s%lld_%s_%d_rgba4444_%dx%d_%d.bmp" ,path, randNum , ptype , LayerIndex ,width, height,index);
		}
    else if(format == HAL_PIXEL_FORMAT_RGB_565) {
		sprintf(fileName , "%s%lld_%s_%d_rgb565_%dx%d_%d.bmp" ,path, randNum , ptype , LayerIndex , width, height,index);
		}
    else if(format == HAL_PIXEL_FORMAT_YCbCr_420_SP) {
		sprintf(fileName , "%s%lld_%s_%d_ybrsp_%dx%d_%d.yuv" ,path, randNum , ptype , LayerIndex , width, height,index);
		}
    else if(format == HAL_PIXEL_FORMAT_YCrCb_420_SP) {
		sprintf(fileName , "%s%lld_%s_%d_yrbsp_%dx%d_%d.yuv" ,path, randNum , ptype , LayerIndex , width, height,index);
		}
    else if(format == HAL_PIXEL_FORMAT_YV12) {
		sprintf(fileName , "%s%lld_%s_%d_yv12_%dx%d_%d.yuv" ,path, randNum , ptype , LayerIndex , width, height,index);
		}
    else if(format == HAL_PIXEL_FORMAT_YCbCr_420_P) {
		sprintf(fileName , "%s%lld_%s_%d_ybrp_%dx%d_%d.yuv" ,path, randNum , ptype , LayerIndex , width, height,index);
		}
    else {
		ALOGE("dump layer failed because of error format %d" , format);
             return -2;
    }
    	
    return dump_bmp(fileName , (void*)pSrc, format,width,height);
}
