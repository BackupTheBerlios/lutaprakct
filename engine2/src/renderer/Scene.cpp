#include "Scene.h"
#include "dae.h"
#include "dae/daeSIDResolver.h"
#include "dom/domCOLLADA.h"
#include "dom/domProfile_COMMON.h"
#include "dae/domAny.h"
#include "dom/domElements.h"

bool Scene::load(char* filename){
	
	collada = new DAE;
	int res = collada->load(filename);
	if (res != DAE_OK){
		delete m_collada;	
		collada = 0;
		return false; 
	}
	
	domCOLLADA *dom = collada->getDom(filename); 
	if ( !dom ){
		delete collada;	
		collada = 0;
		return false; 
	}
	
	domCOLLADA::domSceneRef domScene = dom->getScene();
	daeElement* defaultScene = NULL;
	if (domScene)
		if (domScene->getInstance_visual_scene())
			if (domScene->getInstance_visual_scene())
				defaultScene = domScene->getInstance_visual_scene()->getUrl().getElement();
	if(defaultScene)
		ReadScene( (domVisual_scene *)defaultScene );
	
}