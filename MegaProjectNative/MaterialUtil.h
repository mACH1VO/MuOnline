#pragma once
#include "stdafx.h"

class MaterialUtil
{
public:
	MaterialUtil(void);
	~MaterialUtil(void);

	inline static void setTechniqueOutlinePass(Ogre::Technique* technique)
	{
		/*std::vector<Ogre::Pass*> passes_backup_list;
		for (int i = 0; i < technique->getNumPasses(); i++)
		{
			Ogre::Pass* pass = technique->getPass(i);
			passes_backup_list.push_back(pass);
		}

		technique->removeAllPasses();

		Ogre::Pass* outline_pass = technique->createPass();
		outline_pass->setName("outline_pass");
		outline_pass->setDepthWriteEnabled(false);
		outline_pass->setVertexProgram("glow_vs_cg", false);
		outline_pass->setFragmentProgram("glow_ps_cg", false);*/


	}
};

