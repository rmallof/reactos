/*
 * PROJECT:         ReactOS api tests
 * LICENSE:         GPLv2+ - See COPYING in the top level directory
 * PURPOSE:         COM interface test
 * PROGRAMMER:      Thomas Faber <thomas.faber@reactos.org>
 */

#include "com_apitest.h"

#define NDEBUG
#include <debug.h>

#define myskip(c, ...) ((c) ? 0 : (skip(__VA_ARGS__), 1))
#define mytrace(...) do {       \
    int debug = winetest_debug; \
    winetest_debug = 1;         \
    trace(__VA_ARGS__);         \
    winetest_debug = debug;     \
} while (0)

typedef struct _KNOWN_INTERFACE
{
    const IID *iid;
    PCSTR name;
} KNOWN_INTERFACE;
typedef const KNOWN_INTERFACE *PCKNOWN_INTERFACE;

#undef ID_NAME
#define ID_NAME(c) { &c, #c }
static KNOWN_INTERFACE KnownInterfaces[] =
{
    ID_NAME(IID_IACList),
    ID_NAME(IID_IACList2),
    ID_NAME(IID_IADesktopP2),
    ID_NAME(IID_IAccessible),
    ID_NAME(IID_IAccessControl),
    ID_NAME(IID_IAccessor),
    ID_NAME(IID_IActiveDesktop),
    ID_NAME(IID_IActiveDesktopP),
    ID_NAME(IID_IAddressBarParser),
    ID_NAME(IID_IAddressBand),
    ID_NAME(IID_IAddressEditBox),
    ID_NAME(IID_IAutoComplete),
    ID_NAME(IID_IAutoComplete2),
    ID_NAME(IID_IBandNavigate),
    ID_NAME(IID_IBandProxy),
    ID_NAME(IID_IBandSite),
    ID_NAME(IID_IBandSiteHelper),
    ID_NAME(IID_IBanneredBar),
    ID_NAME(IID_IBindCtx),
    ID_NAME(IID_IBrowserFrameOptions),
    ID_NAME(IID_IBrowserService),
    ID_NAME(IID_IBrowserService2),
    ID_NAME(IID_IBrowserService3),
    ID_NAME(IID_IClassFactory),
    ID_NAME(IID_IClassFactory2),
    ID_NAME(IID_IClassFactory3),
    ID_NAME(IID_IClientSecurity),
    ID_NAME(IID_IComThreadingInfo),
    ID_NAME(IID_IContext),
    ID_NAME(IID_IContextMenu),
    ID_NAME(IID_IContextMenu2),
    ID_NAME(IID_IContextMenu3),
    ID_NAME(IID_IContextMenuCB),
    ID_NAME(IID_IContextMenuSite),
    ID_NAME(IID_IContinue),
    ID_NAME(IID_IDVGetEnum),
    ID_NAME(IID_IDataObject),
    ID_NAME(IID_IDefViewID),
    ID_NAME(IID_IDefViewFrame),
    ID_NAME(IID_IDefViewFrame3),
    ID_NAME(IID_IDefViewFrameGroup),
    ID_NAME(IID_IDefViewSafety),
    ID_NAME(IID_IDefViewScript),
    ID_NAME(IID_IDeskBand),
    ID_NAME(IID_IDeskBandEx),
    ID_NAME(IID_IDeskBar),
    ID_NAME(IID_IDeskBarClient),
    ID_NAME(IID_IDeskMovr),
    ID_NAME(IID_IDispatch),
    ID_NAME(IID_IDockingWindow),
    ID_NAME(IID_IDockingWindowFrame),
    ID_NAME(IID_IDockingWindowSite),
    ID_NAME(IID_IDocViewSite),
    ID_NAME(IID_IDragSourceHelper),
    ID_NAME(IID_IDropSource),
    ID_NAME(IID_IDropTarget),
    ID_NAME(IID_IDropTargetHelper),
    ID_NAME(IID_IEnumExtraSearch),
    ID_NAME(IID_IEnumGUID),
    ID_NAME(IID_IEnumIDList),
    ID_NAME(IID_IEnumShellItems),
    ID_NAME(IID_IEnumString),
    ID_NAME(IID_IEnumUnknown),
    ID_NAME(IID_IEnumVARIANT),
    ID_NAME(IID_IErrorLog),
    ID_NAME(IID_IExplorerToolbar),
    ID_NAME(IID_IExtractIconA),
    ID_NAME(IID_IExtractIconW),
    ID_NAME(IID_IExtractImage),
    ID_NAME(IID_IExtractImage2),
    ID_NAME(IID_IFileDialog),
    ID_NAME(IID_IFileDialog2),
    ID_NAME(IID_IFileSearchBand),
    ID_NAME(IID_IFolderBandPriv),
    ID_NAME(IID_IFolderFilter),
    ID_NAME(IID_IFolderFilterSite),
    ID_NAME(IID_IFolderView),
    ID_NAME(IID_IFolderView2),
    ID_NAME(IID_IFolderViewOC),
    ID_NAME(IID_IFolderViewSettings),
    ID_NAME(IID_IGlobalFolderSettings),
    ID_NAME(IID_IInitializeObject),
    ID_NAME(IID_IInputObject),
    ID_NAME(IID_IInputObjectSite),
    ID_NAME(IID_IInternalUnknown),
    ID_NAME(IID_IMarshal),
    ID_NAME(IID_IMenuBand),
    ID_NAME(IID_IMenuPopup),
    ID_NAME(IID_IMoniker),
    ID_NAME(IID_IMultiMonitorDockingSite),
    ID_NAME(IID_IMultiQI),
    ID_NAME(IID_INamespaceProxy),
    ID_NAME(IID_INameSpaceTreeControl),
    ID_NAME(IID_INSCTree),
    ID_NAME(IID_INSCTree2),
    ID_NAME(IID_IObjMgr),
    ID_NAME(IID_IObjectSafety),
    ID_NAME(IID_IObjectWithSite),
    ID_NAME(IID_IOleCommandTarget),
    ID_NAME(IID_IOleInPlaceActiveObject),
    ID_NAME(IID_IOleInPlaceFrame),
    ID_NAME(IID_IOleInPlaceObject),
    ID_NAME(IID_IOleInPlaceObjectWindowless),
    ID_NAME(IID_IOleInPlaceSite),
    ID_NAME(IID_IOleInPlaceSiteEx),
    ID_NAME(IID_IOleInPlaceSiteWindowless),
    ID_NAME(IID_IOleInPlaceUIWindow),
    ID_NAME(IID_IOleObject),
    ID_NAME(IID_IOleWindow),
    ID_NAME(IID_IPersist),
    ID_NAME(IID_IPersistFile),
    ID_NAME(IID_IPersistFolder),
    ID_NAME(IID_IPersistFolder2),
    ID_NAME(IID_IPersistFolder3),
    ID_NAME(IID_IPersistHistory),
    ID_NAME(IID_IPersistIDList),
    ID_NAME(IID_IPersistMemory),
    ID_NAME(IID_IPersistPropertyBag),
    ID_NAME(IID_IPersistPropertyBag2),
    ID_NAME(IID_IPersistStorage),
    ID_NAME(IID_IPersistStream),
    ID_NAME(IID_IPersistStreamInit),
    ID_NAME(IID_IProgressDialog),
    ID_NAME(IID_IPropertyBag),
    ID_NAME(IID_IPropertyBag2),
    ID_NAME(IID_IQueryAssociations),
    ID_NAME(IID_IQueryInfo),
    ID_NAME(IID_IRegTreeOptions),
    ID_NAME(IID_IRunnableObject),
    ID_NAME(IID_IServerSecurity),
    ID_NAME(IID_IServiceProvider),
    ID_NAME(IID_ISFHelper),
    ID_NAME(IID_IShellBrowser),
    ID_NAME(IID_IShellBrowserService),
    ID_NAME(IID_IShellChangeNotify),
    ID_NAME(IID_IShellDesktopTray),
    ID_NAME(IID_IShellDispatch),
    ID_NAME(IID_IShellDispatch2),
    ID_NAME(IID_IShellDispatch3),
    ID_NAME(IID_IShellDispatch4),
    ID_NAME(IID_IShellDispatch5),
    ID_NAME(IID_IShellExtInit),
    ID_NAME(IID_IShellPropSheetExt),
    ID_NAME(IID_IShellIconOverlayIdentifier),
    ID_NAME(IID_IShellFolder),
    ID_NAME(IID_IShellFolder2),
    ID_NAME(IID_IShellFolderBand),
    ID_NAME(IID_IShellFolderView),
    ID_NAME(IID_IShellFolderViewCB),
    ID_NAME(IID_IShellFolderViewDual),
    ID_NAME(IID_IShellFolderViewDual2),
    ID_NAME(IID_IShellIcon),
    ID_NAME(IID_IShellItem),
    ID_NAME(IID_IShellItem2),
    ID_NAME(IID_IShellItemArray),
    ID_NAME(IID_IShellItemFilter),
    ID_NAME(IID_IShellLinkA),
    ID_NAME(IID_IShellLinkDual),
    ID_NAME(IID_IShellLinkDual2),
    ID_NAME(IID_IShellLinkW),
    ID_NAME(IID_IShellMenu),
    ID_NAME(IID_IShellMenu2),
    ID_NAME(IID_IShellMenuAcc),
    ID_NAME(IID_IShellMenuCallback),
    ID_NAME(IID_IShellNameSpace),
    ID_NAME(IID_IShellService),
    ID_NAME(IID_IShellView),
    ID_NAME(IID_IShellView2),
    ID_NAME(IID_IShellView3),
    ID_NAME(IID_IShellWindows),
    ID_NAME(IID_IStorage),
    ID_NAME(IID_IStream),
    ID_NAME(IID_ISurrogate),
    ID_NAME(IID_ISynchronize),
    ID_NAME(IID_ISynchronizeContainer),
    ID_NAME(IID_ISynchronizeEvent),
    ID_NAME(IID_ISynchronizeHandle),
    ID_NAME(IID_ITaskbarList),
    ID_NAME(IID_ITaskbarList2),
    ID_NAME(IID_ITrackShellMenu),
    ID_NAME(IID_ITrayPriv),
    ID_NAME(IID_ITrayPriv2),
    ID_NAME(IID_IUnknown),
    ID_NAME(IID_IViewObject),
    ID_NAME(IID_IViewObject2),
    ID_NAME(IID_IViewObjectEx),
    ID_NAME(IID_IWinEventHandler),

    ID_NAME(IID_DFConstraint),
    ID_NAME(DIID_DShellFolderViewEvents),

    ID_NAME(IID_CDefView),
    ID_NAME(IID_Folder),
    ID_NAME(IID_Folder2),
    ID_NAME(IID_Folder3),
    ID_NAME(IID_FolderItem),
    ID_NAME(IID_FolderItem2),
    ID_NAME(IID_FolderItems),
    ID_NAME(IID_FolderItems2),
    ID_NAME(IID_FolderItems3),
    ID_NAME(IID_FolderItemVerb),
    ID_NAME(IID_FolderItemVerbs),

    ID_NAME(CLSID_ShellDesktop)
};
static const INT KnownInterfaceCount = RTL_NUMBER_OF(KnownInterfaces);

static
PCKNOWN_INTERFACE
FindInterface(
    _In_ const IID *iid)
{
    INT i;

    for (i = 0; i < KnownInterfaceCount; i++)
        if (IsEqualIID(KnownInterfaces[i].iid, iid))
            return &KnownInterfaces[i];
    ASSERT(i != KnownInterfaceCount);
    return NULL;
}

static
BOOLEAN
IsInterfaceExpected(
    _In_ PCCLASS_AND_INTERFACES class,
    _In_ const IID *iid)
{
    INT i;

    for (i = 0; class->ifaces[i].iid; i++)
        if (IsEqualIID(class->ifaces[i].iid, iid))
            return TRUE;
    return FALSE;
}

#define INTF_NOT_EXPOSED LONG_MAX
static
LONG
GetInterfaceOffset(
    _In_ PUNKNOWN pUnk,
    _In_ const IID *iid)
{
    HRESULT hr;
    PVOID pObj;
    PUNKNOWN pUnk2;
    LONG offset;

    hr = IUnknown_QueryInterface(pUnk, iid, &pObj);
    ok(hr == S_OK || hr == E_NOINTERFACE, "IUnknown::QueryInterface returned 0x%lx\n", hr);
    if (FAILED(hr))
        return INTF_NOT_EXPOSED;

    pUnk2 = pObj;
    offset = (LONG_PTR)pObj - (LONG_PTR)pUnk;
    IUnknown_Release(pUnk2);
    return offset;
}

static
VOID
TestModuleInterfaces(
    _In_ PCCLASS_AND_INTERFACES ExpectedInterfaces,
    _In_ INT ExpectedInterfaceCount)
{
    HRESULT hr;
    PVOID pObj;
    PUNKNOWN pUnk;
    INT iClass, iIntf;
    PCCLASS_AND_INTERFACES class;

    for (iClass = 0; iClass < ExpectedInterfaceCount; iClass++)
    {
        class = &ExpectedInterfaces[iClass];
        hr = CoCreateInstance(class->clsid,
                              NULL,
                              CLSCTX_INPROC_SERVER,
                              &IID_IUnknown,
                              &pObj);
        ok(hr == S_OK, "CoCreateInstance failed. hr=0x%lx\n", hr);
        if (FAILED(hr))
        {
            skip("Failed to instantiate %s.\n", class->name);
            continue;
        }

        pUnk = pObj;

        /* Check that all expected interfaces are present and have the right offset */
        for (iIntf = 0; class->ifaces[iIntf].iid; iIntf++)
        {
            PCKNOWN_INTERFACE iface = FindInterface(class->ifaces[iIntf].iid);
            LONG offset = GetInterfaceOffset(pUnk, iface->iid);
            if (offset == INTF_NOT_EXPOSED)
                ok(0, "%s is missing %s (offset %ld)\n", class->name, iface->name, class->ifaces[iIntf].offset);
            else if (class->ifaces[iIntf].offset != FARAWY)
            {
#ifdef FAIL_WRONG_OFFSET
                ok(offset == class->ifaces[iIntf].offset, "%s, %s offset is %ld, expected %ld\n", class->name, iface->name, offset, class->ifaces[iIntf].offset);
#else
                if (offset != class->ifaces[iIntf].offset)
                    mytrace("%s, %s offset is %ld, expected %ld\n", class->name, iface->name, offset, class->ifaces[iIntf].offset);
#endif
            }
        }

        /* Check that none other than the expected interfaces are present */
        for (iIntf = 0; iIntf < KnownInterfaceCount; iIntf++)
        {
            PCKNOWN_INTERFACE iface = &KnownInterfaces[iIntf];
            LONG offset;
            if (IsInterfaceExpected(class, iface->iid))
                continue;
            offset = GetInterfaceOffset(pUnk, iface->iid);
#ifdef GENERATE_TABLE_ENTRIES
            ok(offset == INTF_NOT_EXPOSED, "%s: { %s%x,   &%s },\n", class->name, offset < 0 ? "-" : "", offset < 0 ? -offset : offset, iface->name);
#else
            ok(offset == INTF_NOT_EXPOSED, "%s exposes %s (offset %ld), but shouldn't\n", class->name, iface->name, offset);
#endif
        }

        // TODO: do some aggregation

        IUnknown_Release(pUnk);
    }
}

static
VOID
TestModuleRegistry(
    _In_ PCWSTR ModuleName,
    _In_ PCCLASS_AND_INTERFACES ExpectedInterfaces,
    _In_ INT ExpectedInterfaceCount)
{
    INT iClass;
    PCCLASS_AND_INTERFACES class;
    HKEY hKeyClasses;
    LONG result;

    result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Classes\\CLSID", 0, KEY_ENUMERATE_SUB_KEYS, &hKeyClasses);
    ok(result == NO_ERROR, "Failed to open classes key, error %lu\n", result);
    if (!myskip(result == NO_ERROR, "No classes key\n"))
    {
        for (iClass = 0; iClass < ExpectedInterfaceCount; iClass++)
        {
            HKEY hKey;
            HKEY hKeyServer;
            NTSTATUS status;
            UNICODE_STRING clsid;
            DWORD type;
            WCHAR data[100];
            DWORD dataSize;
            PCWSTR expectedThreadingModel;

            class = &ExpectedInterfaces[iClass];
            status = RtlStringFromGUID(class->clsid, &clsid);
            ok(status == STATUS_SUCCESS, "Failed to convert guid to string for %s, status %lx\n", class->name, status);
            if (myskip(NT_SUCCESS(status), "No guid string\n"))
                continue;

            result = RegOpenKeyEx(hKeyClasses, clsid.Buffer, 0, KEY_ENUMERATE_SUB_KEYS, &hKey);
            ok(result == NO_ERROR, "Failed to open key for %s, error %lu\n", class->name, result);
            RtlFreeUnicodeString(&clsid);
            if (myskip(result == NO_ERROR, "No key\n"))
                continue;

            result = RegOpenKeyEx(hKey, L"InProcServer32", 0, KEY_QUERY_VALUE, &hKeyServer);
            ok(result == NO_ERROR, "Failed to open key for %s, error %lu\n", class->name, result);
            RegCloseKey(hKey);
            if (myskip(result == NO_ERROR, "No key\n"))
                continue;

            dataSize = sizeof(data);
            result = RegQueryValueEx(hKeyServer, NULL, NULL, &type, (PBYTE)data, &dataSize);
            ok(result == NO_ERROR, "Failed to query value for %s, error %lu\n", class->name, result);
            if (!myskip(result == NO_ERROR, "No module name\n"))
            {
                ok(type == REG_SZ || type == REG_EXPAND_SZ, "type %lu for %s\n", type, class->name);
                ok(dataSize % sizeof(WCHAR) == 0, "size %lu for %s\n", dataSize, class->name);
                ok(dataSize <= sizeof(data), "size %lu for %s\n", dataSize, class->name);
                ok(data[dataSize / sizeof(WCHAR) - 1] == UNICODE_NULL, "Not null terminated for %s\n", class->name);
                // TODO: Use SearchPath (or assume everything's in system32) and do a proper full path compare
                PathStripPathW(data);
                PathRemoveExtensionW(data);
                ok(!wcsicmp(data, ModuleName), "Server is %ls, expected %ls for %s\n", data, ModuleName, class->name);
            }

            dataSize = sizeof(data);
            result = RegQueryValueEx(hKeyServer, L"ThreadingModel", NULL, &type, (PBYTE)data, &dataSize);
            ok(result == NO_ERROR, "Failed to query value for %s, error %lu\n", class->name, result);
            if (!myskip(result == NO_ERROR, "No ThreadingModel\n"))
            {
                ok(type == REG_SZ || type == REG_EXPAND_SZ, "type %lu for %s\n", type, class->name);
                ok(dataSize % sizeof(WCHAR) == 0, "size %lu for %s\n", dataSize, class->name);
                ok(dataSize <= sizeof(data), "size %lu for %s\n", dataSize, class->name);
                ok(data[dataSize / sizeof(WCHAR) - 1] == UNICODE_NULL, "Not null terminated for %s\n", class->name);
                expectedThreadingModel = class->ThreadingModel;
                if (!expectedThreadingModel)
                    expectedThreadingModel = L"Apartment";
                ok(!wcsicmp(data, expectedThreadingModel), "Server is %ls, expected %ls for %s\n", data, expectedThreadingModel, class->name);
            }

            RegCloseKey(hKeyServer);
        }
        RegCloseKey(hKeyClasses);
    }
}

static
VOID
TestManualInstantiation(
    _In_ PCWSTR ModuleName,
    _In_ PCCLASS_AND_INTERFACES ExpectedInterfaces,
    _In_ INT ExpectedInterfaceCount)
{
    INT iClass;
    PCCLASS_AND_INTERFACES class;
    HRESULT (__stdcall *DllGetClassObject)(REFCLSID, REFIID, PVOID *);

    DllGetClassObject = (PVOID)GetProcAddress(GetModuleHandle(ModuleName), "DllGetClassObject");
    ok(DllGetClassObject != NULL, "DllGetClassObject not found in %ls, error %lu\n", ModuleName, GetLastError());
    if (myskip(DllGetClassObject != NULL, "No DllGetClassObject\n"))
        return;

    for (iClass = 0; iClass < ExpectedInterfaceCount; iClass++)
    {
        PVOID pv;
        HRESULT hr;
        class = &ExpectedInterfaces[iClass];
        hr = DllGetClassObject(class->clsid, &IID_IClassFactory, &pv);
        ok(hr == S_OK, "DllGetClassObject failed for %s, hr = 0x%lx\n", class->name, hr);
        if (!myskip(SUCCEEDED(hr), "No class factory\n"))
        {
            IClassFactory *pCF = pv;
            hr = IClassFactory_CreateInstance(pCF, NULL, &IID_IUnknown, &pv);
            ok(hr == S_OK, "IClassFactory::CreateInstance failed for %s, hr = 0x%lx\n", class->name, hr);
            if (!myskip(SUCCEEDED(hr), "No instance\n"))
            {
                IUnknown *pUnk = pv;
                IUnknown_Release(pUnk);
            }
            IClassFactory_Release(pCF);
        }
    }
}

VOID
TestClasses(
    _In_ PCWSTR ModuleName,
    _In_ PCCLASS_AND_INTERFACES ExpectedInterfaces,
    _In_ INT ExpectedInterfaceCount)
{
    HRESULT hr;

    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    ok(hr == S_OK, "CoInitializeEx failed. hr=0x%lx\n", hr);
    if (myskip(SUCCEEDED(hr), "Failed to initialize COM. Cannot perform tests\n"))
        return;

    TestModuleInterfaces(ExpectedInterfaces, ExpectedInterfaceCount);
    TestModuleRegistry(ModuleName, ExpectedInterfaces, ExpectedInterfaceCount);
    TestManualInstantiation(ModuleName, ExpectedInterfaces, ExpectedInterfaceCount);

    CoUninitialize();
}
