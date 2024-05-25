/*

medico:
  - string: nombre
  - los pacientes tienen un orden de llegada
  - elimina de la lista al siguiente paciente

paciente:
  -string: nombre
  - ser atendido por un medico, puede estar esperando a varios medicos
  - no puede pedir consulta a un medico que ya esta esperado (no tiene que estar en la cola del medico dos veces)
  - paciente cansado de esperar, puede abandonar (iterador)
  - lista ordenada de medicos que dejan de atender a este paciente


  unordered_map<medico, list<paciente>> medicos;
  unordered_map<paciente, map<medico, iterator>> pacientes;
*/
