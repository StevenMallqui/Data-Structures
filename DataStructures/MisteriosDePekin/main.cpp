class MisteriosDePekin{
public:
  MisteriosDePekin(const string &culpable){}
  void anyadir_rasgo(const string &sospechoso, const string &rasgo){}
  vector<string> sospechosos() const{}
  void nuevo_jugador(const string &nombre){}
  void jugador_descarta(const string &jugador, const string &rasgo){}
  bool jugador_enganyado(const string &jugador) const{}
  bool puede_detener_culpable(const string &jugador) const
private:
};