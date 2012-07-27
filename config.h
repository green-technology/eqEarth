#pragma once

#include <eq/eq.h>

#include "initData.h"
#include "frameData.h"
#include "view.h"
#include "viewer.h"
#include "controls.h"

#include <osg/Node>

namespace eqEarth
{
class Config : public eq::Config
{
public:
    Config( eq::ServerPtr parent );

protected:
    virtual ~Config( );

public:
    virtual bool init( );
    virtual bool exit( );

    virtual uint32_t startFrame( );
    virtual uint32_t finishFrame( );

    void setInitData( const InitData& initData ) { _initData = initData; }
    const InitData& getInitData( ) const { return _initData; }
    bool mapInitData( const eq::uint128_t& initDataID );

    virtual bool handleEvent( const eq::ConfigEvent* event );

public:
    osgUtil::IncrementalCompileOperation*
        getIncrementalCompileOperation( ) const { return _ico.get( ); }

    osgViewer::View* takeOrCreateOSGView( const eq::uint128_t& sceneID );
    void releaseOSGView( osgViewer::View* view );

#if 0
    CompositeViewer *getViewer( ) { return _viewer; }
    const CompositeViewer *getViewer( ) const { return _viewer; }
#endif

private:
    osg::Group* getScene( const eq::uint128_t& sceneID );

    void cleanup( );

protected:
    InitData _initData;
    FrameData _frameData;

    osg::ref_ptr< osg::Group > _scene;

    osg::ref_ptr< osgUtil::IncrementalCompileOperation > _ico;
    osg::ref_ptr< osgDB::DatabasePager > _pager;

    lunchbox::Lock _viewer_lock;
    osg::ref_ptr< CompositeViewer > _viewer;
    osg::ref_ptr< osgGA::EventQueue > _eventQueue;

    osg::ref_ptr< osg::GraphicsContext > _gc;

    uint32_t _appRenderTick;

private:
    View* selectCurrentView( const eq::uint128_t& viewID );
    void handleMouseEvent( const eq::ConfigEvent* event );
    void updateCurrentWorldPointer( const eq::ConfigEvent* event );

    bool appInitGL( bool pbuffer = true );
};
}
