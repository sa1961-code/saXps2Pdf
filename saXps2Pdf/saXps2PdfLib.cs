using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

namespace saXps2Pdf.COM.saXps2PdfLib
{
    [TypeLibType(TypeLibTypeFlags.FDual | TypeLibTypeFlags.FDispatchable)]
    [Guid("38175A1B-0099-428B-8CC0-D843C76D4A00")]
    [ComImport]
    public interface IsaXps2PdfConvert
    {
        [DispId(101)]
        string Version { [DispId(101), MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)] [return: MarshalAs(UnmanagedType.BStr)] get; }

        [DispId(102)]
        string ErrorMessage { [DispId(102), MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)] [return: MarshalAs(UnmanagedType.BStr)] get; }

        [DispId(201)]
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        bool Convert([MarshalAs(UnmanagedType.BStr), In] string bsSourceFileName, [MarshalAs(UnmanagedType.BStr), In] string bsOutputFileName, bool bPdfA);
    }

    public static class saXps2PdfConvert
    {
        public static IsaXps2PdfConvert Create()
        {
            object obj = CreateObject("38175a1b-0099-428b-8cc0-d843c76d4b00");
            return obj != null ? (IsaXps2PdfConvert)obj : null;
        }

        static object CreateObject(string bsGuid)
        {
            uint CLSCTX_INPROC_SERVER = 1;
            Guid clsid = new Guid(bsGuid);
            Guid IID_IUnknown = new Guid("00000000-0000-0000-C000-000000000046");
            object instance = null;
            uint hResult = CoCreateInstance(ref clsid, null, CLSCTX_INPROC_SERVER, ref IID_IUnknown, out instance);
            return hResult == 0 ? instance : null;
        }

        [DllImport("ole32.Dll")]
        static public extern uint CoCreateInstance(ref Guid clsid,
           [MarshalAs(UnmanagedType.IUnknown)] object inner,
           uint context,
           ref Guid uuid,
           [MarshalAs(UnmanagedType.IUnknown)] out object rReturnedComObject);
    }
}

