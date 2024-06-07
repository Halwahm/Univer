package jdbc;

import java.sql.SQLException;

public class Main {
    public static void main(String[] args) {
        try {
            ConnectorDB connectorDB = new ConnectorDB("localhost:5432/citypopulation", "postgres", "halwa2003");
            connectorDB.getConnection();

            // Вывести информацию обо всех жителях заданного города, разговаривающих на заданном языке
            connectorDB.getResidentsByCityAndLanguage("City1", "English");

            // Вывести информацию обо всех городах, в которых проживают жители выбранного типа
            connectorDB.getCitiesByResidentType("Type1");

            // Вывести информацию о городе с заданным количеством населения и всех типах жителей, в нем проживающих
            connectorDB.getCityByPopulation(10000);

            // Вывести информацию о самом древнем типе жителей
            connectorDB.getOldestResidentType();

            connectorDB.removeConnection();
        } catch (ClassNotFoundException | SQLException e) {
            e.printStackTrace();
        }
    }
}
