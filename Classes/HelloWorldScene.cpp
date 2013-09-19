#include "HelloWorldScene.h"



CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if ( !CCLayer::init() )
	{
		return false;
	}

	CCTMXTiledMap* map = new CCTMXTiledMap();
	map->initWithTMXFile("sample_map.tmx");
	addChild(map, -1,1);
	CCTMXObjectGroup* group = map->objectGroupNamed("path");
	CCArray* objects = group->getObjects();
	//CCDictionary* polyline = (CCDictionary*)group->objectNamed("first");
	//CCLOG("polyline=%s", ((CCString*)polyline->objectForKey("polyline"))->getCString());



	CCDictionary* dict = NULL;
	CCObject* pobj = NULL;
	CCARRAY_FOREACH(objects, pobj)
	{
		dict = (CCDictionary*)pobj;
		if(dict->valueForKey("type")->m_sString == "polygonline")
		{
			//CCLOG("polyline=%s", ((CCString*)dict->objectForKey("polyline"))->getCString());
			ParsePolyline(dict);
		} 
	}
    return true;
}

void HelloWorld::ParsePolyline(CCDictionary* dict)
{

	int offsetPosX = ((CCString*)dict->objectForKey("x"))->intValue();
	int offsetPosY = ((CCString*)dict->objectForKey("y"))->intValue();

	CCString* sPoint = (CCString*)dict->objectForKey("polyline");
	string strPoint = sPoint->m_sString.substr(10,sPoint->m_sString.size());
	const char* chPoint = strPoint.c_str();
	stringstream pointsStream(chPoint);
	string pointPair;
	CCLOG("Polyline : %s", chPoint);
    while(std::getline(pointsStream, pointPair, ' '))
	{
		CCLOG("PointPair : %s", pointPair.c_str());
		stringstream pointStream(pointPair);
		string xStr,yStr;
		char buffer[32] = {0};
        if(std::getline(pointStream, xStr, ','))
		{
			CCLOG("x string : %s", xStr.c_str());
			int x = atoi(xStr.c_str()) + offsetPosX;
			CCLOG("x : %d",x);
		}

		if(std::getline(pointStream, yStr, '\n'))
		{
			int y = atoi(yStr.c_str()) + offsetPosY;
			CCLOG("y : %d",y);
		}
	}

}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
