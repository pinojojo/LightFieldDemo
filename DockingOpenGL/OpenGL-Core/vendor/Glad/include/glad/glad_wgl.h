/*

    WGL loader generated by glad 0.1.35 on Tue Jul 19 07:31:47 2022.

    Language/Generator: C/C++
    Specification: wgl
    APIs: wgl=1.0
    Profile: -
    Extensions:
        WGL_ARB_extensions_string,
        WGL_EXT_extensions_string,
        WGL_NV_gpu_affinity
    Loader: True
    Local files: False
    Omit khrplatform: True
    Reproducible: False

    Commandline:
        --api="wgl=1.0" --generator="c" --spec="wgl" --omit-khrplatform --extensions="WGL_ARB_extensions_string,WGL_EXT_extensions_string,WGL_NV_gpu_affinity"
    Online:
        https://glad.dav1d.de/#language=c&specification=wgl&loader=on&api=wgl%3D1.0&extensions=WGL_ARB_extensions_string&extensions=WGL_EXT_extensions_string&extensions=WGL_NV_gpu_affinity
*/


#ifndef WINAPI
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif
#ifndef NOMINMAX
#define NOMINMAX 1
#endif
#include <windows.h>
#endif

#include <glad/glad.h>

#ifndef __glad_wglext_h_

#ifdef __wglext_h_
#error WGL header already included, remove this include, glad already provides it
#endif

#define __glad_wglext_h_
#define __wglext_h_

#ifndef APIENTRY
#define APIENTRY
#endif
#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (* GLADloadproc)(const char *name);

#ifndef GLAPI
# if defined(GLAD_GLAPI_EXPORT)
#  if defined(_WIN32) || defined(__CYGWIN__)
#   if defined(GLAD_GLAPI_EXPORT_BUILD)
#    if defined(__GNUC__)
#     define GLAPI __attribute__ ((dllexport)) extern
#    else
#     define GLAPI __declspec(dllexport) extern
#    endif
#   else
#    if defined(__GNUC__)
#     define GLAPI __attribute__ ((dllimport)) extern
#    else
#     define GLAPI __declspec(dllimport) extern
#    endif
#   endif
#  elif defined(__GNUC__) && defined(GLAD_GLAPI_EXPORT_BUILD)
#   define GLAPI __attribute__ ((visibility ("default"))) extern
#  else
#   define GLAPI extern
#  endif
# else
#  define GLAPI extern
# endif
#endif

GLAPI int gladLoadWGL(HDC hdc);
GLAPI void gladUnloadWGL(void);

GLAPI int gladLoadWGLLoader(GLADloadproc, HDC hdc);

struct _GPU_DEVICE {
    DWORD  cb;
    CHAR   DeviceName[32];
    CHAR   DeviceString[128];
    DWORD  Flags;
    RECT   rcVirtualScreen;
};
DECLARE_HANDLE(HPBUFFERARB);
DECLARE_HANDLE(HPBUFFEREXT);
DECLARE_HANDLE(HVIDEOOUTPUTDEVICENV);
DECLARE_HANDLE(HPVIDEODEV);
DECLARE_HANDLE(HPGPUNV);
DECLARE_HANDLE(HGPUNV);
DECLARE_HANDLE(HVIDEOINPUTDEVICENV);
typedef struct _GPU_DEVICE GPU_DEVICE;
typedef struct _GPU_DEVICE *PGPU_DEVICE;
#define ERROR_INCOMPATIBLE_AFFINITY_MASKS_NV 0x20D0
#define ERROR_MISSING_AFFINITY_MASK_NV 0x20D1
#ifndef WGL_ARB_extensions_string
#define WGL_ARB_extensions_string 1
GLAPI int GLAD_WGL_ARB_extensions_string;
typedef const char * (APIENTRYP PFNWGLGETEXTENSIONSSTRINGARBPROC)(HDC hdc);
GLAPI PFNWGLGETEXTENSIONSSTRINGARBPROC glad_wglGetExtensionsStringARB;
#define wglGetExtensionsStringARB glad_wglGetExtensionsStringARB
#endif
#ifndef WGL_EXT_extensions_string
#define WGL_EXT_extensions_string 1
GLAPI int GLAD_WGL_EXT_extensions_string;
typedef const char * (APIENTRYP PFNWGLGETEXTENSIONSSTRINGEXTPROC)(void);
GLAPI PFNWGLGETEXTENSIONSSTRINGEXTPROC glad_wglGetExtensionsStringEXT;
#define wglGetExtensionsStringEXT glad_wglGetExtensionsStringEXT
#endif
#ifndef WGL_NV_gpu_affinity
#define WGL_NV_gpu_affinity 1
GLAPI int GLAD_WGL_NV_gpu_affinity;
typedef BOOL (APIENTRYP PFNWGLENUMGPUSNVPROC)(UINT iGpuIndex, HGPUNV *phGpu);
GLAPI PFNWGLENUMGPUSNVPROC glad_wglEnumGpusNV;
#define wglEnumGpusNV glad_wglEnumGpusNV
typedef BOOL (APIENTRYP PFNWGLENUMGPUDEVICESNVPROC)(HGPUNV hGpu, UINT iDeviceIndex, PGPU_DEVICE lpGpuDevice);
GLAPI PFNWGLENUMGPUDEVICESNVPROC glad_wglEnumGpuDevicesNV;
#define wglEnumGpuDevicesNV glad_wglEnumGpuDevicesNV
typedef HDC (APIENTRYP PFNWGLCREATEAFFINITYDCNVPROC)(const HGPUNV *phGpuList);
GLAPI PFNWGLCREATEAFFINITYDCNVPROC glad_wglCreateAffinityDCNV;
#define wglCreateAffinityDCNV glad_wglCreateAffinityDCNV
typedef BOOL (APIENTRYP PFNWGLENUMGPUSFROMAFFINITYDCNVPROC)(HDC hAffinityDC, UINT iGpuIndex, HGPUNV *hGpu);
GLAPI PFNWGLENUMGPUSFROMAFFINITYDCNVPROC glad_wglEnumGpusFromAffinityDCNV;
#define wglEnumGpusFromAffinityDCNV glad_wglEnumGpusFromAffinityDCNV
typedef BOOL (APIENTRYP PFNWGLDELETEDCNVPROC)(HDC hdc);
GLAPI PFNWGLDELETEDCNVPROC glad_wglDeleteDCNV;
#define wglDeleteDCNV glad_wglDeleteDCNV
#endif

#ifdef __cplusplus
}
#endif

#endif