#pragma once

#include "variant.h"
#include "client.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void* DLR_BULK;

DLR_BULK DLR_bulkCreate(size_t count);
void DLR_bulkDelete(DLR_BULK bulk);
size_t DLR_bulkGetCount(DLR_BULK bulk);

DLR_RESULT DLR_bulkSetRequestAddress(DLR_BULK bulk, size_t index, char* address);
DLR_RESULT DLR_bulkSetRequestData(DLR_BULK bulk, size_t index, DLR_VARIANT data);

char* DLR_bulkGetResponseAddress(DLR_BULK bulk, size_t index);
DLR_VARIANT DLR_bulkGetResponseData(DLR_BULK bulk, size_t index);
uint64_t DLR_bulkGetResponseTimestamp(DLR_BULK bulk, size_t index);
DLR_RESULT DLR_bulkGetResponseResult(DLR_BULK bulk, size_t index);

DLR_RESULT DLR_clientBulkReadSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);
DLR_RESULT DLR_clientBulkWriteSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);
DLR_RESULT DLR_clientBulkCreateSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);
DLR_RESULT DLR_clientBulkDeleteSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);
DLR_RESULT DLR_clientBulkBrowseSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);
DLR_RESULT DLR_clientBulkMetadataSync(DLR_CLIENT client, DLR_BULK bulk, const char* token);

#ifdef __cplusplus
}
#endif
