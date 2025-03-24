#pragma once

// Framework
#include "carpc/runtime/comm/async/event/Event.hpp"



namespace application::events {

   enum class eAppEventID { BOOT, SHUTDOWN, PING, UNDEFINED };
   const char* c_str( const eAppEventID );

   struct AppEventData
   {
      std::string message = "";
   };

   struct AppEventSignature
   {
      bool operator<( const AppEventSignature& other ) const;

      std::string dbg_name( ) const;

      std::size_t id = 0;
      std::size_t level = 0;
   };



   DEFINE_EVENT_NOSIG_NODATA( NoSigNoData );
   DEFINE_EVENT_IDSIG_NODATA( IdSigNoData, eAppEventID );
   DEFINE_EVENT_IDSIG( IdSigData, AppEventData, eAppEventID );
   DEFINE_EVENT( SigData, AppEventData, AppEventSignature );

} // namespace application::events
