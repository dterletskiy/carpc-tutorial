#pragma once

// Framework
#include "carpc/runtime/application/RootComponent.hpp"
// Application
#include "imp/app/events/AppEvent.hpp"




namespace application::components::onoff {

   class Component
      : public carpc::application::RootComponent
      , public events::NoSigNoData::Consumer
      , public events::IdSigNoData::Consumer
      , public events::IdSigData::Consumer
      , public events::SigData::Consumer
   {
      public:
         static carpc::application::IComponent::tSptr creator( );

      private:
         Component( const std::string& );
      public:
         ~Component( ) override;

      private:
         void process_event( const events::NoSigNoData::Event& ) override;
         void process_event( const events::IdSigNoData::Event& ) override;
         void process_event( const events::IdSigData::Event& ) override;
         void process_event( const events::SigData::Event& ) override;

      private:
         void process_boot( const std::string& ) override;
         void process_shutdown( carpc::callback::tBlocker ) override;
   };

} // namespace application::components::onoff
