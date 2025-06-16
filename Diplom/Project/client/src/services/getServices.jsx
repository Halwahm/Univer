import $api, { API_URL } from "../https";
export default class getServices {
  static async getFilm() {
    const response = await $api.get("film/Home");

    return response;
  }
  static async GetHistory() {
    return $api.get("auditt/GetHistory");
  }
  static async GetSession() {
    return $api.get("session/GetSession");
  }
  static async GetStatistic() {
    return $api.get("auditt/GetStatistic");
  }
  static async GetDataFilm(formData) {
    return $api.post("film/GetDataFilm", { idFilm: formData });
  }
  static async GetFilmByName(formData) {
    return $api.post("film/GetFilmByName", formData);
  }
  static async GetUserIntoSession(idsession) {
    return $api.post("ticket/GetUserIntoSession", { idsession: idsession });
  }
  static async GetFavFilm(idfilm) {
    return $api.post("favorite/GetFavFilm", { idFilm: idfilm });
  }
  static async GetFavoriteFilm() {
    return $api.get("favorite/GetFavoriteFilm");
  }
  static async Dellorder(id, idsession, coast_set, chatr_id) {
    return $api.delete("ticket/Dellorder", {
      data: {
        id: id,
        idsession: idsession,
        coast_set: coast_set,
        chatr_id: chatr_id,
      },
    });
  }
  static async GetFilmGenre(formData) {
    return $api.post("film/GetFilmGenre", { idGenre: formData });
  }
  static async GetTicketUser() {
    const response = await $api.get("ticket/GetTicketUser");
    return response;
  }
  static async GetGenreFilm() {
    return $api.get("genre/GetGenreFilm");
  }
  static async GetUsers() {
    return $api.get("user/GetUsers");
  }
  static async GetFilmHall() {
    return $api.get("film/GetFilmHall");
  }
  static async GetUserById() {
    return $api.get("user/GetUserById");
  }
  static async GetAllHall() {
    return $api.get("hall");
  }
  static async GetHallById(id) {
    return $api.get(`hall/${id}`);
  }
  static async GetAllGenres() {
    return $api.get("genre");
  }
  static async GetGenreById(id) {
    return $api.get(`genre/${id}`);
  }
}
