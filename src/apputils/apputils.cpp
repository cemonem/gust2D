#include <apputils/apputils.h>

float WINDOW_SIZE_PX_Y = 600;
float WINDOW_SIZE_PX_X = 800;
float PX_PER_METER = 50;
float ARROWHEAD_PX_LENGTH = 5;
float ARROWHEAD_ANGLE_RAD = 0.1f;
float POINT_PX_RADIUS = 2;
float TFORM_AXES_PX_LENGTH = 20;



static Tform2 _getGustTformFromTiledObject(tinyxml2::XMLElement const *object) {
    Tform2 tform = Tform2(Vec2(object->FloatAttribute("x")/PX_PER_METER, -object->FloatAttribute("y")/PX_PER_METER),
                          -object->FloatAttribute("rotation")*gust_DEG2RAD);
    Vec2 size = Vec2(object->FloatAttribute("width")/PX_PER_METER, -object->FloatAttribute("height")/PX_PER_METER);
    tform.translation = tform*(size/2.0f);
    return tform;
}

static tinyxml2::XMLElement const *_getPropertyWithName(tinyxml2::XMLElement const *root, 
                                                        std::string const &name) {
    for(auto *property = root->FirstChildElement("properties")->FirstChildElement("property");
        property;
        property = property->NextSiblingElement("property")) {
            if(std::string(property->Attribute("name")) == name) {
                return property;
            }
        }
    return nullptr;
}

template <typename T>
static T _getPropertyValueWithName(tinyxml2::XMLElement const *root, std::string const &name) {
    tinyxml2::XMLElement const *property = _getPropertyWithName(root, name);
    T value;
    auto result = property->QueryAttribute("value", &value);
    if(result != tinyxml2::XML_SUCCESS) {
        std::cout << "Failed to get property value for property: " << name << "\n";
    }
    return value;
}

static Rigidbody2& _makeRigidbodyFromTiledObject(tinyxml2::XMLElement const *object, PhysicsEngine2 &engine) {
    Tform2 tform = _getGustTformFromTiledObject(object);
    tinyxml2::XMLElement const *rigidbodyProperty = nullptr;
    for(tinyxml2::XMLElement const *property = object->FirstChildElement("properties")->FirstChildElement("property");
        property;
        property = property->NextSiblingElement("property")) {
            if(std::string(property->Attribute("name")) == "rigidbody") {
                rigidbodyProperty = property;
                break;
            }
        }
    if(!rigidbodyProperty) {
        std::cerr << "No rigidbody property found for object: " << object->Attribute("id") << "\n";
        return engine.createBody(tform, 1.0f, 1.0f);
    }
    else {
        Rigidbody2& body = engine.createBody(tform,
                                             _getPropertyValueWithName<float>(rigidbodyProperty, "mass"),
                                             _getPropertyValueWithName<float>(rigidbodyProperty, "inertia"),
                                             Vec2(_getPropertyValueWithName<float>(rigidbodyProperty, "velocity_x"),
                                                  _getPropertyValueWithName<float>(rigidbodyProperty, "velocity_y")),
                                             _getPropertyValueWithName<float>(rigidbodyProperty, "angularVelocity"),
                                             _getPropertyValueWithName<float>(rigidbodyProperty, "linearDamping"),
                                             _getPropertyValueWithName<float>(rigidbodyProperty, "angularDamping"));
        if(_getPropertyValueWithName<bool>(rigidbodyProperty, "massInfinite")) {
            body.setMassInfinite();
        }
        if(_getPropertyValueWithName<bool>(rigidbodyProperty, "inertiaInfinite")) {
            body.setInertiaInfinite();
        }
        return body;
    }
}


std::vector<std::unique_ptr<DebugGameObject>> makeShapesFromTMXFile(char const *fileName, PhysicsEngine2 &engine) {
    std::vector<std::unique_ptr<DebugGameObject>> shapes;
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(fileName) == tinyxml2::XML_SUCCESS) {
        tinyxml2::XMLElement const *root = doc.FirstChildElement("map")->FirstChildElement("objectgroup");
        if (root) {
            for (tinyxml2::XMLElement const *object = root->FirstChildElement("object"); 
                 object; 
                 object = object->NextSiblingElement("object")) {
                    std::string shapeType = object->Attribute("type");
                    if(shapeType == "circle") {
                        assert(object->FloatAttribute("width") == object->FloatAttribute("height"));
                        real radius = object->FloatAttribute("width")/(PX_PER_METER*2.0f);
                        Rigidbody2& body = _makeRigidbodyFromTiledObject(object, engine);
                        engine.createCircleCollider(body, radius);
                        shapes.emplace_back(std::make_unique<DebugCircleGameObject>(body, radius));
                    }
                    else if(shapeType == "rectangle") {
                        Rigidbody2& body = _makeRigidbodyFromTiledObject(object, engine);
                        Vec2 halfSize = Vec2(object->FloatAttribute("width")/PX_PER_METER/2.0f, 
                                         object->FloatAttribute("height")/PX_PER_METER/2.0f);
                        engine.createRectangleCollider(body, halfSize);
                        shapes.emplace_back(std::make_unique<DebugRectangleGameObject>(body, halfSize));
                    }
                    else {
                        std::cerr << "Unknown template name: " << shapeType << "\n";
                    }
                }
            }
        else {
            std::cerr << "Ill-formed TMX file. \n";
        }
    } 
    else {
        std::cerr << "Failed to load TMX file. \n";
    }
    return shapes;
}