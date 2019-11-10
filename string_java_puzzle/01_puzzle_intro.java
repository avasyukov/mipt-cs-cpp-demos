class Demo
{ 
    public static void main(String[] args)
    {
        String data = "";
        for(Integer i = 0; i < 10; ++i) {
            data += i.toString();
        }
        System.out.println("Test complete: " + data);
    }
}
