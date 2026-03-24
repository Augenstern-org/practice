package top.neuroil;

public class Menu {
    private String options;
    private int options_count;

    public Menu() {
        options = "";
        options_count = 0;
    }

    public void addOptions(String content) {
        options_count++;
        options += options_count + ") " + content + "\n";
    }

    public String display() {
        return options;
    }

    public String getOptions(int k){
        if(k > 0 && k <= options_count){
            String[] splStrings = options.split("\\n");
            return splStrings[k-1].substring(3);
        }
        return "Wrong options_count.";
    }

    public static void main(String[] args) {
        Menu myMenu = new Menu();
        myMenu.addOptions("test1");
        myMenu.addOptions("test2");
        myMenu.addOptions("test3");

        System.out.println(myMenu.display());
        System.out.println(myMenu.getOptions(2));
    }
}
