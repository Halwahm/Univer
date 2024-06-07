package jdbc;

import java.sql.*;

public class ConnectorDB {
    private Connection connection;
    private String url;
    private String user;
    private String pass;

    public ConnectorDB(String url, String user, String pass) throws ClassNotFoundException {
        this.url = url;
        this.user = user;
        this.pass = pass;
    }

    public void getConnection() throws SQLException {
        connection = DriverManager.getConnection("jdbc:postgresql://" + url, user, pass);
        if (!connection.isClosed())
            System.out.println("Connection successful");
    }

    public void removeConnection() throws SQLException {
        System.out.println("Close connection");
        if (connection != null && !connection.isClosed()) {
            connection.close();
        }
    }

    public void closeStatement(Statement statement) throws SQLException {
        if (statement != null && !statement.isClosed()) {
            statement.close();
        }
    }

    public void getResidentsByCityAndLanguage(String city, String language) throws SQLException {
        String sql = "SELECT rt.name " +
                "FROM cities c " +
                "INNER JOIN residenttypes rt ON c.cityid = rt.cityid " +
                "WHERE c.name = ? AND rt.language = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, city);
            preparedStatement.setString(2, language);
            ResultSet resultSet = preparedStatement.executeQuery();
            System.out.println("Residents of " + city + " speaking " + language + ":");
            while (resultSet.next()) {
                String residentName = resultSet.getString("name");
                System.out.println(residentName);
            }
        }
    }

    public void getCitiesByResidentType(String residentType) throws SQLException {
        String sql = "SELECT c.name " +
                "FROM cities c " +
                "INNER JOIN residenttypes rt ON c.cityid = rt.cityid " +
                "WHERE rt.name = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setString(1, residentType);
            ResultSet resultSet = preparedStatement.executeQuery();
            System.out.println("Cities with residents of type " + residentType + ":");
            while (resultSet.next()) {
                String cityName = resultSet.getString("name");
                System.out.println(cityName);
            }
        }
    }

    public void getCityByPopulation(int population) throws SQLException {
        String sql = "SELECT c.name, rt.name, rt.language " +
                "FROM cities c " +
                "INNER JOIN residenttypes rt ON c.cityid = rt.cityid " +
                "WHERE c.totalpopulation = ?";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            preparedStatement.setInt(1, population);
            ResultSet resultSet = preparedStatement.executeQuery();
            System.out.println("City with population " + population + ":");
            while (resultSet.next()) {
                String cityName = resultSet.getString(1);
                String residentName = resultSet.getString(2);
                String language = resultSet.getString(3);
                System.out.println("City: " + cityName + ", Resident: " + residentName + ", Language: " + language);
            }
        }
    }

    public void getOldestResidentType() throws SQLException {
        String sql = "SELECT name " +
                "FROM residenttypes " +
                "ORDER BY residenttypeid ASC " +
                "LIMIT 1";
        try (PreparedStatement preparedStatement = connection.prepareStatement(sql)) {
            ResultSet resultSet = preparedStatement.executeQuery();
            System.out.println("Oldest resident type:");
            while (resultSet.next()) {
                String oldestResidentType = resultSet.getString("name");
                System.out.println(oldestResidentType);
            }
        }
    }
}

