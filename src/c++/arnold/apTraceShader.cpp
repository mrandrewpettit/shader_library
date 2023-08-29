// cl /LD apTraceShader.cpp /I %ARNOLD_PATH%\include %ARNOLD_PATH%\lib\ai.lib /link /out:apTraceShader.dll

#include <ai.h>

AI_SHADER_NODE_EXPORT_METHODS(apTraceShaderMethods);

namespace ASTR {
	const AtString matrix("matrix");
};

namespace
{
	enum apTraceShaderParams {
		p_position,
		p_direction,
		p_opacity,
		p_selfTraceset,
		p_breakEdge
	};
}

void SampleShaderGlobals(AtShaderGlobals*& sgA, AtShaderGlobals* sgB)
{
	sgA->x = sgB->x;
	sgA->y = sgB->y;
	sgA->px = sgB->px;
	sgA->py = sgB->py;
	sgA->si = sgB->si;
	sgA->transp_index = sgB->transp_index;
	sgA->Ro = sgB->Ro;
	sgA->Rd = sgB->Rd;
	sgA->Rl = sgB->Rl;
	sgA->tid = sgB->tid;
	sgA->Rt = sgB->Rt;
	sgA->bounces = sgB->bounces;
	sgA->bounces_diffuse = sgB->bounces_diffuse;
	sgA->bounces_specular = sgB->bounces_specular;
	sgA->bounces_reflect = sgB->bounces_reflect;
	sgA->bounces_transmit = sgB->bounces_transmit;
	sgA->bounces_volume = sgB->bounces_volume;
	sgA->fhemi = sgB->fhemi;
	sgA->time = sgB->time;
	sgA->Op = sgB->Op;
	sgA->proc = sgB->proc;
	sgA->shader = sgB->shader;
	sgA->psg = sgB->psg;
	sgA->Po = sgB->Po;
	sgA->P = sgB->P;
	sgA->dPdx = sgB->dPdx;
	sgA->dPdy = sgB->dPdy;
	sgA->N = sgB->N;
	sgA->Nf = sgB->Nf;
	sgA->Ng = sgB->Ng;
	sgA->Ngf = sgB->Ngf;
	sgA->Ns = sgB->Ns;
	sgA->bu = sgB->bu;
	sgA->bv = sgB->bv;
	sgA->u = sgB->u;
	sgA->v = sgB->v;
	sgA->fi = sgB->fi;
	sgA->M = sgB->M;
	sgA->Minv = sgB->Minv;
	sgA->light_filter = sgB->light_filter;
	sgA->nlights = sgB->nlights;
	sgA->dPdu = sgB->dPdu;
	sgA->dPdv = sgB->dPdv;
	sgA->dDdx = sgB->dDdx;
	sgA->dDdy = sgB->dDdy;
	sgA->dNdx = sgB->dNdx;
	sgA->dNdy = sgB->dNdy;
	sgA->dudx = sgB->dudx;
	sgA->dudy = sgB->dudy;
	sgA->dvdx = sgB->dvdx;
	sgA->dvdy = sgB->dvdy;
	sgA->skip_shadow = sgB->skip_shadow;
	sgA->sc = sgB->sc;
	sgA->inclusive_traceset = sgB->inclusive_traceset;
	sgA->traceset = sgB->traceset;
}

node_parameters
{
	AiParameterVec("position", 0.0, 0.0, 0.0);
	AiParameterVec("direction", 0.0, 0.0, 0.0);
	AiParameterRGB("opacity", 1.0, 1.0, 1.0);
	AiParameterStr("selfTraceset", "");
	AiParameterBool("breakEdge", 0);
}

node_initialize {}

node_update {}

node_finish {}

// TODO: remove cards that hit target object not viewable by camera

// TODO: houdini -> split object, wrap cards to split, add seam cards

shader_evaluate
{
	// get shader parameters
	AtVector pos = AiShaderEvalParamVec(p_position);
	AtVector dir = AiShaderEvalParamVec(p_direction);
	AtRGB opacity = AiShaderEvalParamOpacity(p_opacity);
	AtString selfTraceset = AiShaderEvalParamStr(p_selfTraceset);
	bool breakEdge = AiShaderEvalParamBool(p_breakEdge);

	// set global trace set
	if (selfTraceset.length() > 0)
		AiShaderGlobalsSetTraceSet(sg, selfTraceset, false); // false => exclusive traceset, the rays should not trace themselves (i.e. cards should not trace other cards)

	// sample target object
	AtShaderGlobals* sg_targetObjectHit = AiShaderGlobals();
	AtRay targetObjectRay = AiMakeRay(AI_RAY_DIFFUSE_REFLECT, pos, &dir, AI_BIG, sg); // MAYBE: AI_RAY_CAMERA huge bug makeing this AI_RAY_CAMERA need to look into it
	if (AiTraceProbe(targetObjectRay, sg_targetObjectHit))
	{
		// check if card sis sampling unseen face
		if (AiV3Dot(sg_targetObjectHit->Nf, sg->Rd) > 0)
			opacity *= AI_RGB_BLACK;
			// leave the parent if statement

		// check if sampled point is visible to camera
		AtShaderGlobals* sg_camRayHit = AiShaderGlobals();
		if (selfTraceset.length() > 0)
			AiShaderGlobalsSetTraceSet(sg, selfTraceset, false);

		// handle silhouette break
		if (!breakEdge)
		{
			AtRay camRay = AiMakeRay(AI_RAY_DIFFUSE_REFLECT, sg->Ro, &sg->Rd, AI_BIG, sg); // AI_RAY_DIFFUSE_REFLECT should work even if target object primary visibility is disabled
			AiTraceProbe(camRay, sg_camRayHit);
			 
			if (sg_camRayHit->Op != sg_targetObjectHit->Op)
				opacity *= AI_RGB_BLACK;
		}

		// ad tech to check if card ray hit part of target object facing away from camera

		AiShaderEvaluate(AiShaderGlobalsGetShader(sg_targetObjectHit), sg_targetObjectHit);
		SampleShaderGlobals(sg, sg_targetObjectHit);

		// cleanup
		AiShaderGlobalsDestroy(sg_camRayHit);
	}
	else
	{
		opacity *= AI_RGB_BLACK;
	}

	// cleanup
	AiShaderGlobalsUnsetTraceSet(sg);
	AiShaderGlobalsDestroy(sg_targetObjectHit);

	sg->out.CLOSURE() = sg_targetObjectHit->out.CLOSURE();
	sg->out.CLOSURE() *= opacity;
	sg->out.CLOSURE().add(AiClosureTransparent(sg, 1 - opacity));

}

node_loader
{
	if (i > 0)
		return false;
	node->methods = apTraceShaderMethods;
	node->output_type = AI_TYPE_CLOSURE;
	node->name = "apTrace";
	node->node_type = AI_NODE_SHADER;
	strcpy(node->version, AI_VERSION);
	return true;
}
