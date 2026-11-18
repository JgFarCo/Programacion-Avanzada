module com.mechadeluel.mechaduel {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.mechadeluel.mechaduel to javafx.fxml;
    exports com.mechadeluel.mechaduel;
}