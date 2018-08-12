#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>

static bool isRunning;

LRESULT CALLBACK MainWindowCallback(
HWND   windowHandle,
UINT   message,
WPARAM wParam,
LPARAM lParam
)
{
    LRESULT result = 0;
    
    switch(message){
        case WM_SIZE:
        {
            OutputDebugStringA("size size\n");
        } break;
        
        case WM_CLOSE:
        {
            isRunning = false;
        } break;
        
        case WM_DESTROY:
        {
            isRunning = false;
            OutputDebugStringA("destroy destroy\n");
        } break;
        
        case WM_ACTIVATEAPP:
        {
            OutputDebugStringA("activate activate\n");
        } break;
        
        case WM_PAINT:
        {
            PAINTSTRUCT paint;
            HDC deviceContext = BeginPaint(windowHandle, &paint);
            int x = paint.rcPaint.left;
            int y = paint.rcPaint.top;
            int height = paint.rcPaint.bottom - paint.rcPaint.top;
            int width = paint.rcPaint.right - paint.rcPaint.left;
            PatBlt(deviceContext, x, y, width, height, WHITENESS);
            EndPaint(windowHandle, &paint);
        } break;
        default:
        {
            OutputDebugStringA("Random aja\n");
            result = DefWindowProc(windowHandle, message, wParam, lParam);
        } break;
    }
    
    
    return(result);
}

int CALLBACK WinMain(
HINSTANCE instance,
HINSTANCE prevInstance,
LPSTR     commmandLine,
int       showCode )
{
    WNDCLASS windowClass = {};
    windowClass.style = CS_OWNDC;
    windowClass.lpfnWndProc = MainWindowCallback;
    windowClass.hInstance = instance;
    // windowClass.hIcon =;
    windowClass.lpszClassName= "BagusFantasyWindowClass";
    
    if(RegisterClass(&windowClass)){
        HWND windowHandle = 
            CreateWindowEx(
            0,
            windowClass.lpszClassName,
            "Bagus Fantasy",
            WS_OVERLAPPEDWINDOW|WS_VISIBLE,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            instance,
            0);
        if(windowHandle){
            isRunning = true;
            for(;isRunning;){
                MSG message;
                BOOL messageResult = GetMessageA(&message, 0,0,0);
                if(messageResult>0){
                    TranslateMessage(&message);
                    DispatchMessageA(&message);
                }
                else {
                    break;
                }
            }
        }
        else{
            //logging
        }
    }
    else{
        //logging
    }
    return 0;
}
#else
#include <stdio.h>
int main(){
    printf("REPLACE THIS WITH SOMETHING REAL\n");
    return 0;
}
#endif
