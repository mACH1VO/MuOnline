#include "StdAfx.h"
#include "MuRenderQueueListener.h"
#include "GameFramework.h"
#include "MUEnums.h"

using namespace Ogre;

MuRenderQueueListener::MuRenderQueueListener(void)
{
}


MuRenderQueueListener::~MuRenderQueueListener(void)
{
}

		/** Event raised before all render queues are processed. 
		*/
		void MuRenderQueueListener::preRenderQueues()
		{
			
		}

		/** Event raised after all render queues are processed. 
		*/
		void MuRenderQueueListener::postRenderQueues()
		{

		}

        /** Event raised before a queue group is rendered. 
        @remarks
            This method is called by the SceneManager before each queue group is
            rendered. 
        @param queueGroupId The id of the queue group which is about to be rendered
		@param invocation Name of the invocation which is causing this to be 
			called (@see RenderQueueInvocation)
		@param skipThisInvocation A boolean passed by reference which is by default set to 
			false. If the event sets this to true, the queue will be skipped and not
			rendered. Note that in this case the renderQueueEnded event will not be raised
			for this queue group.
        */
        void MuRenderQueueListener::renderQueueStarted(uint8 queueGroupId, const String& invocation, 
			bool& skipThisInvocation)
        { 
			if ( queueGroupId == RENDER_QUEUE_INVENTORY_ITEM)
			{
				RenderSystem* rs = GameFramework::getSingletonPtr()->renderSystem;
				Matrix4 ortho_proj_trick = GameFramework::getSingletonPtr()->cameraMan->camera_ortho_tricker->getProjectionMatrixRS();
				Matrix4 view_trick = GameFramework::getSingletonPtr()->cameraMan->camera_ortho_tricker->getViewMatrix();
				rs->_setProjectionMatrix(ortho_proj_trick);
				rs->_setViewMatrix(view_trick);
			}

			/*if ( queueGroupId == RENDER_QUEUE_INVENTORY_ITEM_GLOW)
			{

				RenderSystem* rs = GameFramework::getSingletonPtr()->renderSystem;
				Matrix4 ortho_proj_trick = GameFramework::getSingletonPtr()->camera_ortho_tricker->getProjectionMatrixRS();
				Matrix4 view_trick = GameFramework::getSingletonPtr()->camera_ortho_tricker->getViewMatrix();
				rs->_setProjectionMatrix(ortho_proj_trick);
				rs->_setViewMatrix(view_trick);

				Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
				rendersys->setStencilCheckEnabled(true); 
				rendersys->setStencilBufferParams(Ogre::CMPF_NOT_EQUAL,
					STENCIL_VALUE_FOR_OUTLINE_GLOW, STENCIL_FULL_MASK, STENCIL_VALUE_FOR_OUTLINE_GLOW,
					Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE,false);      
			}*/



			if (queueGroupId == RENDER_QUEUE_GLOW_OBJECTS) // outline glow object 
			{ 
				//Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
				/*rendersys->clearFrameBuffer(Ogre::FBT_STENCIL); 
				rendersys->setStencilCheckEnabled(true); 
				rendersys->setStencilBufferParams(Ogre::CMPF_ALWAYS_PASS,
					STENCIL_VALUE_FOR_OUTLINE_GLOW, STENCIL_FULL_MASK, STENCIL_VALUE_FOR_OUTLINE_GLOW,
					Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE, false);     */  
			} 

			if (queueGroupId == RENDER_QUEUE_OUTLINE_GLOW_GLOWS)  // outline glow
			{ 
				/*Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
				rendersys->setStencilCheckEnabled(true); 
				rendersys->setStencilBufferParams(Ogre::CMPF_NOT_EQUAL,
					STENCIL_VALUE_FOR_OUTLINE_GLOW, STENCIL_FULL_MASK, STENCIL_VALUE_FOR_OUTLINE_GLOW,
					Ogre::SOP_KEEP,Ogre::SOP_KEEP,Ogre::SOP_REPLACE,false);      */ 
			} 
			
		}

        /** Event raised after a queue group is rendered. 
        @remarks
            This method is called by the SceneManager after each queue group is
            rendered. 
        @param queueGroupId The id of the queue group which has just been rendered
		@param invocation Name of the invocation which is causing this to be 
			called (@see RenderQueueInvocation)
		@param repeatThisInvocation A boolean passed by reference which is by default set to 
			false. If the event sets this to true, the queue which has just been
			rendered will be repeated, and the renderQueueStarted and renderQueueEnded
			events will also be fired for it again.
        */
        void MuRenderQueueListener::renderQueueEnded(uint8 queueGroupId, const String& invocation, 
			bool& repeatThisInvocation)
        { 
			if ( queueGroupId == RENDER_QUEUE_INVENTORY_ITEM)
			{
				RenderSystem* rs = GameFramework::getSingletonPtr()->renderSystem;
				Matrix4 ortho_proj_trick = GameFramework::getSingletonPtr()->camera->getProjectionMatrixRS();
				Matrix4 view_trick = GameFramework::getSingletonPtr()->camera->getViewMatrix();
				rs->_setProjectionMatrix(ortho_proj_trick);
				rs->_setViewMatrix(view_trick);
			}

			/*if ( queueGroupId == RENDER_QUEUE_INVENTORY_ITEM_GLOW)
			{

				RenderSystem* rs = GameFramework::getSingletonPtr()->renderSystem;
				Matrix4 ortho_proj_trick = GameFramework::getSingletonPtr()->camera->getProjectionMatrixRS();
				Matrix4 view_trick = GameFramework::getSingletonPtr()->camera->getViewMatrix();
				rs->_setProjectionMatrix(ortho_proj_trick);
				rs->_setViewMatrix(view_trick);

				Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
				rendersys->setStencilCheckEnabled(false); 
				rendersys->setStencilBufferParams();
			}*/


			if (queueGroupId == RENDER_QUEUE_GLOW_OBJECTS) // outline glow object 
			{ 
				/*Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
				rendersys->setStencilCheckEnabled(false); 
				rendersys->setStencilBufferParams();    */  
			}

			if (queueGroupId == RENDER_QUEUE_OUTLINE_GLOW_GLOWS)  // outline glow
			{ 
				/*Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton().getRenderSystem(); 
				rendersys->setStencilCheckEnabled(false); 
				rendersys->setStencilBufferParams();      */
			} 
		}
