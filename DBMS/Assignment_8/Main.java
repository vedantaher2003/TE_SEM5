import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSetMetaData;
import java.util.*;

public class Main {
	
	static void createTable(Scanner sc, Connection connection, Statement statement) throws SQLException {
		
		String sql = "CREATE TABLE ";
		
		System.out.print("Enter table name : ");
		String tableName = sc.next();
		sql += tableName + " (";
		
		System.out.print("Enter number of columns : ");
		int noCols = sc.nextInt();
		
		String name, datatype;
		while(noCols-->0) {
			 System.out.print("Enter col name and datatype: ");
			 name = sc.next();
			 datatype = sc.next();
			 sql += name + " " + datatype + ", ";
		}
		
		sql = sql.substring(0, sql.length()-1);
		sql = sql.substring(0, sql.length()-1);
		sql += ")";
		
		statement.execute(sql);
		System.out.println("Table created successfully !!");
		
	}
	
	static void insertData(Scanner sc, Connection connection, Statement statement) throws SQLException {
		
		String sql = "INSERT INTO ";
		
		System.out.print("Enter table name : ");
		String tableName = sc.next();
		
		sql += tableName + " VALUES (";
		
		System.out.print("Enter number of columns : ");
		int noCols = sc.nextInt();
		
		String value;
		while(noCols-->0) {
			 System.out.print("Enter value : ");
			 value = sc.next();
			 sql +=  "'"+ value + "'" + ", ";
		}
		sql = sql.substring(0, sql.length()-1);
		sql = sql.substring(0, sql.length()-1);
		sql += " )";
		

		statement.executeUpdate(sql);
		System.out.println("Data inserted successfully !!");
		
	}
	
	static void readData(Scanner sc, Connection connection, Statement statement, ResultSet resultset) throws SQLException {
		
		String sql = "SELECT * FROM ";
		
		System.out.print("Enter table name : ");
		String tableName = sc.next();
		
		sql += tableName;
		
		resultset = statement.executeQuery(sql);
		
		ResultSetMetaData rsMetaData = resultset.getMetaData();
		int colCount = rsMetaData.getColumnCount();
		
		while(resultset.next()) {
			for(int i=1; i<=colCount; i++) {
				System.out.print(resultset.getString(i) + " ");
			}
		}
		
		resultset.close();
	}
	
	static void updateData(Scanner sc, Connection connection, Statement statement) throws SQLException {
		
		String sql = "UPDATE ";
		
		System.out.print("Enter table name : ");
		String tableName = sc.next();
		
		sql += tableName;
		
		System.out.println("Enter colname and new value to be updated : ");
		String colName = sc.next();
		String newValue = sc.next();
		
		sql += " SET " + colName + "=" + "'" + newValue + "'";
		
		System.out.println("Enter colname for (=) condition and the existing value : ");
		String condColName = sc.next();
		String oldValue = sc.next();
		
		sql += " WHERE " + condColName + " = " + "'" + oldValue + "'";
		
		statement.executeUpdate(sql);
		System.out.println("Data updated successfully !!");
		
	}
	
	static void deleteData(Scanner sc, Connection connection, Statement statement) throws SQLException {
		
		String sql = "DELETE FROM ";
		
		System.out.print("Enter table name : ");
		String tableName = sc.next();
		
		sql += tableName;
		
		System.out.println("Enter colname for (=) condition and the existing value : ");
		String condColName = sc.next();
		String oldValue = sc.next();
		
		sql += " WHERE " + condColName + " = " + "'" + oldValue + "'";
		
		statement.executeUpdate(sql);
		System.out.println("Data deleted successfully !!");
		
	}
	
	public static void main(String[] args) throws SQLException {
		
		Connection connection = null;
		Statement statement = null;
		ResultSet resultset = null;
		
		String url = "jdbc:mariadb://localhost:3306/assi8";
		String user = "root";
		String password = "password";
		
		Scanner sc = new Scanner(System.in);
		
		try {
			
			connection = DriverManager.getConnection(url, user, password);
			System.out.println("Connected Successfully to " + url);
			
			statement = connection.createStatement();
			
			createTable(sc, connection, statement);
			insertData(sc, connection, statement);
			readData(sc, connection, statement, resultset);
			updateData(sc, connection, statement);
			deleteData(sc, connection, statement);
			
		} catch (SQLException e) {
			e.printStackTrace();
		} finally {
			statement.close();
			connection.close();
			sc.close();
		}

	}

}
