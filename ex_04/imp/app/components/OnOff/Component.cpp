// Application
#include "imp/app/components/OnOff/Component.hpp"

#include "carpc/trace/Trace.hpp"
#define CLASS_ABBR "OnOff"



using namespace application::components::onoff;



carpc::application::IComponent::tSptr Component::creator( )
{
   return std::shared_ptr< Component >( new Component( "OnOff" ) );
}

Component::Component( const std::string& _name )
   : carpc::application::RootComponent( _name )
{
   MSG_DBG( "Created: %s", name( ).c_str( ) );

   {
      using tEvent = events::NoSigNoData;
      tEvent::Event::set_notification( this );
   }

   {
      using tEvent = events::IdSigNoData;
      tEvent::Event::set_notification( this, tEvent::UserSignature{ events::eAppEventID::PING } );
      tEvent::Event::set_notification( this, events::eAppEventID::PING );
   }

   {
      using tEvent = events::IdSigData;
      tEvent::Event::set_notification( this, tEvent::UserSignature{ events::eAppEventID::SHUTDOWN } );
      tEvent::Event::set_notification( this, events::eAppEventID::SHUTDOWN );
   }

   {
      using tEvent = events::SigData;
      tEvent::Event::set_notification( this, tEvent::UserSignature{ 0x123, 0x456 } );
      tEvent::Event::set_notification( this, 0x123, 0x456 );
   }
}

Component::~Component( )
{
   MSG_DBG( "Destroyed: %s", name( ).c_str( ) );
}

void Component::process_boot( const std::string& command )
{
   MSG_DBG( "%s", command.c_str( ) );
   events::NoSigNoData::Event::create( )->send( );
}

void Component::process_shutdown( carpc::callback::tBlocker blocker )
{
   MSG_DBG( "shutting down application" );
}

void Component::process_event( const events::NoSigNoData::Event& event )
{
   MSG_DBG( "NoSigNoData" );

   events::IdSigNoData::Event::create( { events::eAppEventID::PING } )->send( );
}

void Component::process_event( const events::IdSigNoData::Event& event )
{
   const auto& event_id = event.info( ).id( );

   MSG_DBG( "IdSigNoData signature: id = '%s'", events::c_str( event_id ) );

   events::IdSigData::Event::create( { events::eAppEventID::SHUTDOWN } )->
      data( { "shutdown message" } )->send( );
}

void Component::process_event( const events::IdSigData::Event& event )
{
   const auto& event_id = event.info( ).id( );
   const auto& event_data = event.data( ) ? *( event.data( ) ) : events::IdSigData::Data{ };

   MSG_DBG( "IdSigData signature: id = '%s'", events::c_str( event_id ) );
   MSG_DBG( "IdSigData data: message = '%s'", event_data.message.c_str( ) );

   switch( event_id )
   {
      case events::eAppEventID::SHUTDOWN:
      {
         shutdown( );
         break;
      }
      default: break;
   }
}

void Component::process_event( const events::SigData::Event& event )
{
   const auto& event_info = event.info( );
   const auto& event_data = event.data( ) ? *( event.data( ) ) : events::SigData::Data{ };

   MSG_DBG( "SigData: id = '%zu' / level = '%zu'", event_info.id, event_info.level );
   MSG_DBG( "SigData data: message = '%s'", event_data.message.c_str( ) );
}
