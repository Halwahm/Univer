import $api from "../https";

export default class AddServices {
  static async AddFilm(formData) {
    return $api.post("film/AddFilm", formData);
  }
  static async BuyTicket(tickets, sessions, IdFilm, fullPrice, coast_set) {
    return $api.post("ticket/BuyTicket", {
      tickets: tickets,
      sessions: sessions,
      IdFilm: IdFilm,
      fullPrice: fullPrice,
      coast_set: coast_set,
    });
  }
  static async AddHall(formData) {
    return $api.post("hall/AddHall", formData);
  }
  static async AddSessions(formData) {
    return $api.post("session/AddSession", formData);
  }
  static async addFavorite(idfilm, id) {
    return $api.post("favorite/addFavorite", { idfilm: idfilm });
  }
  static async removeFavorite(idfilm, id) {
    return $api.post("favorite/removeFavorite", { idfilm: idfilm, id: id });
  }
  static async DeleteTicket(idTicket, chatr_id, coast_set) {
    return $api.delete("ticket/DeleteTicket", {
      data: { idTicket: idTicket, coast_set: coast_set, chatr_id: chatr_id },
    });
  }
  static async DeleteSession(idFilm) {
    return $api.delete("session/DeleteSession", {
      data: { idSession: idFilm },
    });
  }
  static async DeleteFilm(idFilm) {
    return $api.delete("film/DeleteFilm", {
      data: { idFilm: idFilm },
    });
  }
  static async DeleteUser(idUser) {
    return $api.delete("user/DeleteUser", { data: { idUser: idUser } });
  }
  static async UnDeleteUser(idUser) {
    return $api.delete("user/UnDeleteUser", { data: { idUser: idUser } });
  }
  static async CheckTicketCon(data) {
    console.log("3" + data);
    return $api.post("ticket/CheckTicketCon", {
      data: { decodedText: data },
    });
  }
  static async ChangeUserInfo(formData) {
    return $api.put("user/ChangeUserInfo", formData);
  }
  static async UpdateHall(id, formData) {
    return $api.patch(`hall/${id}`, formData);
  }
  static async DeleteHall(id) {
    return $api.delete(`hall/${id}`);
  }
  static async UpdateGenre(id, formData) {
    return $api.patch(`genre/${id}`, formData);
  }
  static async DeleteGenre(id) {
    return $api.delete(`genre/${id}`);
  }
}
