/* Demo Quaternion: free open-source prototype demo of quaternion functionality.
Copyright(C) 2017  Cyprian Tayrien
GNU General Public License <http://www.gnu.org/licenses/>./**/
#include "demoquat.h"
#include "engine.h"

#include "objects/globe/Globe.h"
Globe* globe;

#include "objects/arrows/Arrow.h"
Arrow* beijing;
Arrow* nyc;

#include "objects/arrows/lerparrow.h"
lerparrow* lerper;

#include "objects/arrows/slerparrow.h"
slerparrow* slerper;

object *qtvector, *qavector, *qbvector;

void demoquat()
{
	engine::cam.tform.loc.z = 2;
	engine::cam.isdebug = true;

	beijing = (Arrow*)engine::scene.spawn(new Arrow);
	beijing->tform.setyawpitchroll(glm::vec3{ 89, 359, 0 } * 3.14f / 180.f);

	nyc = (Arrow*)engine::scene.spawn(new Arrow);
	nyc->tform.setyawpitchroll(glm::vec3{ 0, 0, 0 } * 3.14f / 180.f);

	lerper = (lerparrow*) engine::scene.spawn(new lerparrow);
	lerper->a = &(nyc->tform);
	lerper->b = &(beijing->tform);

	qtvector = engine::scene.spawn(new object);
	qtvector->mod = model({ "objects/arrows/bolt.dat" });
	qtvector->tform.scale *= 1.0f / 3000.0f;

	qavector = engine::scene.spawn(new object);
	qavector->mod = model({ "objects/arrows/bolt.dat" });
	qavector->tform.scale *= 1.0f / 3000.0f;

	qbvector = engine::scene.spawn(new object);
	qbvector->mod = model({ "objects/arrows/bolt.dat" });
	qbvector->tform.scale *= 1.0f / 3000.0f;

	slerper = (slerparrow*)engine::scene.spawn(new slerparrow);
	slerper->a = &(nyc->tform);
	slerper->b = &(beijing->tform);
	slerper->qtvector = &qtvector->tform;
	slerper->qavector = &qavector->tform;
	slerper->qbvector = &qbvector->tform;

	globe = (Globe*)engine::scene.spawn(new Globe);
	globe->tform.setyawpitchroll(glm::vec3{ 0, 85, 0 } * 3.14f / 180.f);
}