#include <Python.h>
#include <stdio.h>

static PyObject* createArchive(PyObject* self, PyObject* args) {
    char *name;
    if (!PyArg_ParseTuple(args, "s", &name))
    {
        PyErr_SetString(PyExc_TypeError, "Expected two string as arguments: filename");
        return NULL;
    }
    FILE *textfile;
    textfile = fopen(name, "w");
    if (!textfile) {
        PyErr_SetString(PyExc_IOError, "Cannot create file");
        return NULL;
    }

    fclose(textfile);
    Py_RETURN_NONE;
}

static PyObject* readFile(PyObject* self, PyObject* args) {
    char *filename;
    int linesToRead;
    char lines[linesToRead];
    if (!PyArg_ParseTuple(args, "si", &filename, &linesToRead)) {
        PyErr_SetString(PyExc_TypeError, "Expected one string and one integer as arguments");
        return NULL; 
    }
    FILE *file;
    file = fopen(filename, "r");
    if (!file) {
        PyErr_SetString(PyExc_IOError, "Couldn't open file");
        return NULL;
    }
    while (fgets(lines, sizeof(lines), file) != NULL) {
        printf("%s", lines);
    }
    fclose(file);
    Py_RETURN_NONE;
}

static PyObject* writeFile(PyObject* self, PyObject* args) {
    char *filename;
    char *text;
    if (!PyArg_ParseTuple(args, "ss", &filename, &text)) {
        PyErr_SetString(PyExc_TypeError, "Expected two strings: filename and text");
        return NULL; 
    }

    FILE *file;
    file = fopen(filename, "w");
    if (!file) {
        PyErr_SetString(PyExc_IOError, "Couldn't open file");
        return NULL;
    }
    fprintf(file, text);
    fclose(file);
    Py_RETURN_NONE;
}

static PyMethodDef Metodos[] = {
    {"createFile", createArchive, METH_VARARGS, "Creates a file"},
    {"readFile", readFile, METH_VARARGS, "reads a File"},
    {"writeFile", writeFile, METH_VARARGS, "writes in a file"}, 
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef modulo = {
    PyModuleDef_HEAD_INIT,
    "textlib",
    NULL,
    -1,
    Metodos
};

PyMODINIT_FUNC PyInit_textlib(void) {
    return PyModule_Create(&modulo);
}