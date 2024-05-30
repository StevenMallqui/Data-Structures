  if(tree.empty()){
      mayorArea = 0;
      if(tree.root())

   }else if(tree.left().empty() && tree.right().empty()){
      if(tree.root())
         mayorArea = 0;
      else
         mayorArea = 1;
   }else{
      int areaIz = area_mayor_sin_barreras(tree.left());
      int areaDer = area_mayor_sin_barreras(tree.right());
      if(tree.root())
         mayorArea = max(areaIz, areaDer);
      else

   }


      int mayorArea;
   bool barrera;
   if(tree.empty()){
      mayorArea = 0;
      barrera = true;
   }else if(tree.left().empty() && tree.right().empty()){
      if(tree.root())
         mayorArea = 0;
      else 
         mayorArea = 1;
      
      barrera = tree.root();
   }else{
      auto[areaIz, barreraIz] = area_mayor_sin_barreras_aux(tree.left());
      auto[areaDer, barreraDer] = area_mayor_sin_barreras_aux(tree.right());
      if(!tree.root()){
         if(!barreraIz && barreraDer){
            mayorArea = max((areaIz + 1), areaDer);
         }else if(barreraIz && !barreraDer){
            mayorArea = max(areaIz, (areaDer + 1));
         }else if(barreraIz && barreraDer){
            mayorArea = max(areaIz, areaDer);
         }else if(!barreraIz && !barreraDer){
            mayorArea = areaIz + areaDer;
         }
      }else{
         mayorArea = max(areaIz, areaDer);
      }
      barrera = tree.root();
   }

   return {mayorArea, barrera};