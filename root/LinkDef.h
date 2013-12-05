#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ class Event+;

          //fObjects.push_back(new TObject(*onfile.fObjects[i]));
#pragma read sourceClass="Event" targetClass="Event" \
  source="std::vector<TObject*> fObjects"  version="[1]" \
  target="fObjects" \
  code= "{\
        fObjects.clear();\
        for(int i=0; i<onfile.fObjects.size(); i++) {\
          fObjects.push_back(onfile.fObjects[i]);\
          int unique_id = fObjects.back()->GetUniqueID();\
          fObjects.back()->SetUniqueID(unique_id+100);\
        }\
        }"

#endif
