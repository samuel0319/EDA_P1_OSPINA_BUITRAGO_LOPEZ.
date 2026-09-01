#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct Operacion {
    string tipo;
    int posicion;
    string contenidoAnterior;
    string contenidoNuevo;
};

class Pila {
private:
    Operacion* datos;
    int cantidad;
    int capacidad;

public:
    Pila() {
        capacidad = 4;
        cantidad = 0;
        datos = new Operacion[capacidad];
    }

    ~Pila() {
        delete[] datos;
    }

    bool isEmpty() {
        return cantidad == 0;
    }

    int size() {
        return cantidad;
    }

    void push(Operacion op) {
        if (cantidad == capacidad) {
            capacidad *= 2;

            Operacion* nuevo = new Operacion[capacidad];

            for (int i = 0; i < cantidad; i++) {
                nuevo[i] = datos[i];
            }

            delete[] datos;
            datos = nuevo;
        }

        datos[cantidad] = op;
        cantidad++;
    }

    void pop() {
        if (!isEmpty()) {
            cantidad--;
        }
    }

    Operacion top() {
        return datos[cantidad - 1];
    }
};

void quitarEspacioInicial(string& texto) {
    if (!texto.empty() && texto[0] == ' ') {
        texto.erase(0, 1);
    }
}

int main() {
    Pila undo;
    Pila redo;

    string documento = "";

    ifstream archivo("data/eventos.txt");

    if (!archivo.is_open()) {
        cout << "No se pudo abrir el archivo data/eventos.txt" << endl;
        return 1;
    }

    string linea;

    while (getline(archivo, linea)) {

        if (linea.empty()) {
            continue;
        }

        stringstream ss(linea);

        string comando;
        ss >> comando;

        if (comando == "EDIT") {

            string tipo;
            int posicion;

            ss >> tipo;
            ss >> posicion;

            string contenido;
            getline(ss, contenido);
            quitarEspacioInicial(contenido);

            Operacion op;

            op.tipo = tipo;
            op.posicion = posicion;

            if (tipo == "INSERT") {

                op.contenidoAnterior = "";
                op.contenidoNuevo = contenido;

                documento.insert(op.posicion, op.contenidoNuevo);

                undo.push(op);

                // una nueva edicion borra redo
                while (!redo.isEmpty()) {
                    redo.pop();
                }
            }

            else if (tipo == "DELETE") {

                op.contenidoAnterior = contenido;
                op.contenidoNuevo = "";

                documento.erase(
                    op.posicion,
                    op.contenidoAnterior.length()
                );

                undo.push(op);

                while (!redo.isEmpty()) {
                    redo.pop();
                }
            }

            else if (tipo == "REPLACE") {

                size_t separador = contenido.find('|');

                if (separador == string::npos) {
                    cout << "REPLACE invalido" << endl;
                    continue;
                }

                op.contenidoAnterior = contenido.substr(0, separador);
                op.contenidoNuevo = contenido.substr(separador + 1);

                documento.replace(
                    op.posicion,
                    op.contenidoAnterior.length(),
                    op.contenidoNuevo
                );

                undo.push(op);

                while (!redo.isEmpty()) {
                    redo.pop();
                }
            }
        }

        else if (comando == "UNDO") {

            if (!undo.isEmpty()) {

                Operacion opUndo = undo.top();

                if (opUndo.tipo == "INSERT") {

                    documento.erase(
                        opUndo.posicion,
                        opUndo.contenidoNuevo.length()
                    );
                }

                else if (opUndo.tipo == "DELETE") {

                    documento.insert(
                        opUndo.posicion,
                        opUndo.contenidoAnterior
                    );
                }

                else if (opUndo.tipo == "REPLACE") {

                    documento.replace(
                        opUndo.posicion,
                        opUndo.contenidoNuevo.length(),
                        opUndo.contenidoAnterior
                    );
                }

                undo.pop();
                redo.push(opUndo);

                cout << "UNDO exitoso" << endl;
            }

            else {
                cout << "UNDO no-op: pila vacia" << endl;
            }
        }

        else if (comando == "REDO") {

            if (!redo.isEmpty()) {

                Operacion opRedo = redo.top();

                if (opRedo.tipo == "INSERT") {

                    documento.insert(
                        opRedo.posicion,
                        opRedo.contenidoNuevo
                    );
                }

                else if (opRedo.tipo == "DELETE") {

                    documento.erase(
                        opRedo.posicion,
                        opRedo.contenidoAnterior.length()
                    );
                }

                else if (opRedo.tipo == "REPLACE") {

                    documento.replace(
                        opRedo.posicion,
                        opRedo.contenidoAnterior.length(),
                        opRedo.contenidoNuevo
                    );
                }

                redo.pop();
                undo.push(opRedo);

                cout << "REDO exitoso" << endl;
            }

            else {
                cout << "REDO no-op: pila vacia" << endl;
            }
        }

        cout << "Documento actual: " << documento << endl;
    }

    archivo.close();

    cout << endl;
    cout << "RESULTADO FINAL" << endl;
    cout << "Documento final: " << documento << endl;
    cout << "Elementos en Undo: " << undo.size() << endl;
    cout << "Elementos en Redo: " << redo.size() << endl;

    return 0;
}
