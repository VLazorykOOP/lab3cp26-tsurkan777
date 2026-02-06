import java.util.ArrayList;
import java.util.List;

/* =======================
   PROTOTYPE
   ======================= */
interface DocumentPrototype {
    DocumentPrototype clone();
}

class Document implements DocumentPrototype {
    private String title;
    private String content;

    public Document(String title, String content) {
        this.title = title;
        this.content = content;
    }

    @Override
    public DocumentPrototype clone() {
        return new Document(title, content);
    }

    public void show() {
        System.out.println("Документ: " + title + " | Вміст: " + content);
    }
}

/* =======================
   COMPOSITE
   ======================= */
interface FileSystemComponent {
    void show();
}

class FileLeaf implements FileSystemComponent {
    private String name;

    public FileLeaf(String name) {
        this.name = name;
    }

    @Override
    public void show() {
        System.out.println("Файл: " + name);
    }
}

class FolderComposite implements FileSystemComponent {
    private String name;
    private List<FileSystemComponent> children = new ArrayList<>();

    public FolderComposite(String name) {
        this.name = name;
    }

    public void add(FileSystemComponent component) {
        children.add(component);
    }

    @Override
    public void show() {
        System.out.println("Папка: " + name);
        for (FileSystemComponent c : children) {
            c.show();
        }
    }
}

/* =======================
   TEMPLATE METHOD
   ======================= */
abstract class DocumentProcessor {

    // шаблонний метод
    public final void process() {
        open();
        edit();
        save();
    }

    protected void open() {
        System.out.println("Відкриття документа");
    }

    protected abstract void edit();

    protected void save() {
        System.out.println("Збереження документа");
    }
}

class TextDocumentProcessor extends DocumentProcessor {
    @Override
    protected void edit() {
        System.out.println("Редагування текстового документа");
    }
}

class PdfDocumentProcessor extends DocumentProcessor {
    @Override
    protected void edit() {
        System.out.println("Редагування PDF документа");
    }
}

/* =======================
   MAIN
   ======================= */
public class Main {
    public static void main(String[] args) {

        System.out.println("=== Prototype ===");
        Document template = new Document("Шаблон", "Типовий текст");
        Document copy1 = (Document) template.clone();
        Document copy2 = (Document) template.clone();
        copy1.show();
        copy2.show();

        System.out.println("\n=== Composite ===");
        FolderComposite root = new FolderComposite("Root");
        root.add(new FileLeaf("file1.txt"));
        root.add(new FileLeaf("file2.pdf"));

        FolderComposite docs = new FolderComposite("Documents");
        docs.add(new FileLeaf("doc1.docx"));
        docs.add(new FileLeaf("doc2.docx"));

        root.add(docs);
        root.show();

        System.out.println("\n=== Template Method ===");
        DocumentProcessor textProcessor = new TextDocumentProcessor();
        DocumentProcessor pdfProcessor = new PdfDocumentProcessor();

        textProcessor.process();
        System.out.println();
        pdfProcessor.process();
    }
}
