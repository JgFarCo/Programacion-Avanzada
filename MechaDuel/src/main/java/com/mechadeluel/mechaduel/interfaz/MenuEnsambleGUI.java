package com.mechadeluel.mechaduel.interfaz;

import com.mechadeluel.mechaduel.modelo.MechaTanque;
import com.mechadeluel.mechaduel.modelo.MechaVeloz;
import com.mechadeluel.mechaduel.modelo.MechaAtacante;
import com.mechadeluel.mechaduel.modelo.Robot;
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

public class MenuEnsambleGUI extends Application {

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Mecha Duel - Fase de Preparación");

        Label lblTitulo = new Label("¡Bienvenido a Mecha Duel!\nEmpieza configurando tu robot (suma de estadísticas debe ser igual a 200");

        Label lblArquetipo = new Label("Selecciona el arquetipo de tu mecha: ");
        ComboBox<String> cmbArquetipo = new ComboBox<>();
        cmbArquetipo.getItems().addAll("Mecha Tanque", "Mecha Veloz", "Mecha Atacante");
        cmbArquetipo.setValue("Mecha Tanque"); //esto aca es para que mecha tanque sea la opcion por defecto
        cmbArquetipo.setMaxWidth(Double.MAX_VALUE);

        TextField txtAtk = new TextField(); txtAtk.setPromptText("Ataque (ATK)");
        TextField txtDef = new TextField(); txtDef.setPromptText("Defensa (DEF)");
        TextField txtSpd = new TextField(); txtSpd.setPromptText("Velocidad (SPD)");
        TextField txtNrg = new TextField(); txtNrg.setPromptText("Energia (NRG)");

        Button btnEnsamblar = new Button("Ensamblar tu Robot");
        Label lblMensaje = new Label();

        btnEnsamblar.setOnAction(e -> {
            try{
                int atk = Integer.parseInt(txtAtk.getText());
                int def = Integer.parseInt(txtDef.getText());
                int spd = Integer.parseInt(txtSpd.getText());
                int nrg = Integer.parseInt(txtNrg.getText());

                String tipoSeleccionado = cmbArquetipo.getValue();
                Robot miRobot;

                if("Mecha Tanque".equals(tipoSeleccionado)) {
                    miRobot = new MechaTanque(atk, def, spd, nrg);
                }
                if("Mecha Veloz".equals(tipoSeleccionado)) {
                    miRobot = new MechaVeloz(atk, def, spd, nrg);
                } else {
                    miRobot = new MechaAtacante(atk, def, spd, nrg);
                }

                lblMensaje.setStyle("-fx-text-fill: green; -fx-font-weight: bold;");
                lblMensaje.setText("¡El robot (" + tipoSeleccionado + ") se pudo ensamblar con exito!\nPuntos de salud iniciales: " + miRobot.getHp());
            } catch(NumberFormatException ex) {
                lblMensaje.setStyle("-fx-text-fill: red;");
                lblMensaje.setText("Error: Solo puedes ingresar numeros enteros");
            } catch(IllegalArgumentException ex) {
                lblMensaje.setStyle("-fx-text-fill: red;");
                lblMensaje.setText(ex.getMessage());
            }
                }
                );
        VBox root = new VBox(12, lblTitulo, txtAtk, txtDef, txtSpd, txtNrg, btnEnsamblar, lblMensaje);
        root.setPadding(new Insets(20));

        Scene scene = new Scene(root, 380, 420);
        primaryStage.setScene(scene);
        primaryStage.show();

    }

    public static void main(String[] args) {
        launch(args);
    }
}
