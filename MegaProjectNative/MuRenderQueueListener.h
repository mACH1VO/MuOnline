#pragma once
#include "stdafx.h"

using namespace Ogre;

class MuRenderQueueListener : public Ogre::RenderQueueListener
{
public:
	MuRenderQueueListener(void);
	~MuRenderQueueListener(void);

	/** Event raised before all render queues are processed. 
		*/
		virtual void preRenderQueues();
		/** Event raised after all render queues are processed. 
		*/
		virtual void postRenderQueues();


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
        virtual void renderQueueStarted(uint8 queueGroupId, const String& invocation, 
			bool& skipThisInvocation);

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
        virtual void renderQueueEnded(uint8 queueGroupId, const String& invocation, 
			bool& repeatThisInvocation);

};

