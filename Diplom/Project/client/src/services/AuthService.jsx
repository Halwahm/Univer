import $api, { API_URL } from "../https";
export default class AuthService {
  static async login(email, password) {
    return $api.post("user/sign-in", { email, password });
  }
  static async logout() {
    return $api.delete("user/logout");
  }
  static async checkAuth() {
    return $api.get(`${API_URL}user/refresh`);
  }
}
