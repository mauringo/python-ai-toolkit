#pragma once
#include "variant.h"

#ifdef __cplusplus
extern "C" {
#endif

  typedef void* DLR_SUBSCRIPTION;

  typedef struct DLR_NOTIFY_ITEM
  {
    DLR_VARIANT data; // data of the notify item
    DLR_VARIANT info; // containing notify_info.fbs (address, timestamp, type, ...)
  }DLR_NOTIFY_ITEM;

  //! Publishes new data for this subscription
  //! @param[in] subscription   Reference to the subscription
  //! @param[in] status         Status of notification. On failure subscription is canceled for all items.
  //! @param[in] items          Notification items
  //! @return result
  DLR_RESULT DLR_SubscriptionPublish(DLR_SUBSCRIPTION subscription, DLR_RESULT status, DLR_NOTIFY_ITEM* items, size_t count);

  //! Returns properties of subscription
  //! @param[in] subscription   Reference to the subscription
  //! @return Properties of Subscription in a Variant (see sub_properties.fbs)
  DLR_VARIANT DLR_SubscriptionGetProps(DLR_SUBSCRIPTION subscription);

  //! Returns nodes subscribed for this subscription
  //! @param[in] subscription   Reference to the subscription
  //! @param[out] nodes         Subscribed nodes as array of strings
  void DLR_SubscriptionGetNodes(DLR_SUBSCRIPTION subscription, DLR_VARIANT nodes);

  //! Returns current timestamp
  //! @param[in] subscription   Reference to the subscription
  //! @return timestamp
  uint64_t DLR_SubscriptionGetTimestamp(DLR_SUBSCRIPTION subscription);

#ifdef __cplusplus
}
#endif
