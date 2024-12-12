#pragma once

#include <Windows.h>
#include <winternl.h>

struct _RTL_BALANCED_NODE {
    union {
        struct _RTL_BALANCED_NODE* Children[2];                             //0x0
        struct {
            struct _RTL_BALANCED_NODE* Left;                                //0x0
            struct _RTL_BALANCED_NODE* Right;                               //0x8
        };
    };

    union {
        struct {
            UCHAR Red : 1;                                                    //0x10
            UCHAR Balance : 2;                                                //0x10
        };

        ULONGLONG ParentValue;                                              //0x10
    };
};

enum _LDR_HOT_PATCH_STATE {
    LdrHotPatchBaseImage = 0,
    LdrHotPatchNotApplied = 1,
    LdrHotPatchAppliedReverse = 2,
    LdrHotPatchAppliedForward = 3,
    LdrHotPatchFailedToPatch = 4,
    LdrHotPatchStateMax = 5
};

enum _LDR_DLL_LOAD_REASON {
    LoadReasonStaticDependency = 0,
    LoadReasonStaticForwarderDependency = 1,
    LoadReasonDynamicForwarderDependency = 2,
    LoadReasonDelayloadDependency = 3,
    LoadReasonDynamicLoad = 4,
    LoadReasonAsImageLoad = 5,
    LoadReasonAsDataLoad = 6,
    LoadReasonEnclavePrimary = 7,
    LoadReasonEnclaveDependency = 8,
    LoadReasonPatchImage = 9,
    LoadReasonUnknown = -1
};


struct __LDR_DATA_TABLE_ENTRY {
    struct _LIST_ENTRY     InLoadOrderLinks;                                    //0x0
    struct _LIST_ENTRY     InMemoryOrderLinks;                                  //0x10
    struct _LIST_ENTRY     InInitializationOrderLinks;                          //0x20
    VOID* DllBase;                                                          //0x30
    VOID* EntryPoint;                                                       //0x38
    ULONG                  SizeOfImage;                                                      //0x40
    struct _UNICODE_STRING FullDllName;                                     //0x48
    struct _UNICODE_STRING BaseDllName;                                     //0x58
    union {
        UCHAR FlagGroup[4];                                                 //0x68
        ULONG Flags;                                                        //0x68
        struct {
            ULONG PackagedBinary : 1;                                         //0x68
            ULONG MarkedForRemoval : 1;                                       //0x68
            ULONG ImageDll : 1;                                               //0x68
            ULONG LoadNotificationsSent : 1;                                  //0x68
            ULONG TelemetryEntryProcessed : 1;                                //0x68
            ULONG ProcessStaticImport : 1;                                    //0x68
            ULONG InLegacyLists : 1;                                          //0x68
            ULONG InIndexes : 1;                                              //0x68
            ULONG ShimDll : 1;                                                //0x68
            ULONG InExceptionTable : 1;                                       //0x68
            ULONG ReservedFlags1 : 2;                                         //0x68
            ULONG LoadInProgress : 1;                                         //0x68
            ULONG LoadConfigProcessed : 1;                                    //0x68
            ULONG EntryProcessed : 1;                                         //0x68
            ULONG ProtectDelayLoad : 1;                                       //0x68
            ULONG ReservedFlags3 : 2;                                         //0x68
            ULONG DontCallForThreads : 1;                                     //0x68
            ULONG ProcessAttachCalled : 1;                                    //0x68
            ULONG ProcessAttachFailed : 1;                                    //0x68
            ULONG CorDeferredValidate : 1;                                    //0x68
            ULONG CorImage : 1;                                               //0x68
            ULONG DontRelocate : 1;                                           //0x68
            ULONG CorILOnly : 1;                                              //0x68
            ULONG ChpeImage : 1;                                              //0x68
            ULONG ChpeEmulatorImage : 1;                                      //0x68
            ULONG ReservedFlags5 : 1;                                         //0x68
            ULONG Redirected : 1;                                             //0x68
            ULONG ReservedFlags6 : 2;                                         //0x68
            ULONG CompatDatabaseProcessed : 1;                                //0x68
        };
    };

    USHORT                      ObsoleteLoadCount;                            //0x6c
    USHORT                      TlsIndex;                                     //0x6e
    struct _LIST_ENTRY          HashLinks;                                    //0x70
    ULONG                       TimeDateStamp;                                //0x80
    struct _ACTIVATION_CONTEXT* EntryPointActivationContext;                  //0x88
    VOID* Lock;                                                               //0x90
    VOID* DdagNode;                                                           //0x98
    struct _LIST_ENTRY          NodeModuleLink;                               //0xa0
    VOID* LoadContext;                                                        //0xb0
    VOID* ParentDllBase;                                                      //0xb8
    VOID* SwitchBackContext;                                                  //0xc0
    struct _RTL_BALANCED_NODE   BaseAddressIndexNode;                         //0xc8
    struct _RTL_BALANCED_NODE   MappingInfoIndexNode;                         //0xe0
    ULONGLONG                   OriginalBase;                                 //0xf8
    union _LARGE_INTEGER        LoadTime;                                     //0x100
    ULONG                       BaseNameHashValue;                            //0x108
    enum _LDR_DLL_LOAD_REASON   LoadReason;                                   //0x10c
    ULONG                       ImplicitPathOptions;                          //0x110
    ULONG                       ReferenceCount;                               //0x114
    ULONG                       DependentLoadFlags;                           //0x118
    UCHAR                       SigningLevel;                                 //0x11c
    ULONG                       CheckSum;                                     //0x120
    VOID* ActivePatchImageBase;                                               //0x128
    enum _LDR_HOT_PATCH_STATE   HotPatchState;                                //0x130
};