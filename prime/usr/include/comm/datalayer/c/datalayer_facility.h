typedef enum Facility
{
  DL_COMMON = 0,        // common   
  DL_APPLICATION = 1,    // eg. Data invalid, node not available, ...
  DL_COMMUNICATION = 2,  // ZMQ related communcation errors
  DL_CLIENT = 3,         // internal client errors
  DL_PROVIDER = 4,       // internal provider errors
  DL_BROKER = 5,         // internal broker errors
  DL_REALTIME = 6,       // datalayer realtime related errors
  DL_SECURITY = 7        // datalayer security related errors
}Facility;
