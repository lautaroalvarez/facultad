import java.util.*;
import java.awt.*;
import java.awt.geom.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import java.security.*;
import javax.swing.*;

public class AGMTester {
    int N;
    int a[];
    int b[];
    int l[];

    int padresUF[];

    void initUF(int n)
    {
        padresUF = new int[n];
        for(int i=0;i<n;i++)
            padresUF[i] = i;
    }

    int find(int t)
    {
        if(padresUF[t] == t)
            return t;
        padresUF[t] = find(padresUF[t]);
        return padresUF[t];
    }

    void join(int a, int b)
    {
        padresUF[find(a)] = find(b);
    }

    void generate(String seed) {
        try {
            SecureRandom r1 = SecureRandom.getInstance("SHA1PRNG");
            long seedVal = Long.parseLong(seed);
            r1.setSeed(seedVal);
            N = r1.nextInt(1000)+5;
            int M = r1.nextInt(10000)+3;
            while(M > (N*(N-1))/4 || M < N)
                M = r1.nextInt(100000)+1;
            ArrayList<Integer> a2 = new ArrayList<>();
            ArrayList<Integer> b2 = new ArrayList<>();
            initUF(N);
            HashSet<Integer> ejes = new HashSet<>();
            for(int i=0;i<M;i++)
            {
                int f = r1.nextInt(N);
                int t = r1.nextInt(N);
                while(f == t || ejes.contains(f*10000+t))
                {
                    f = r1.nextInt(N);
                    t = r1.nextInt(N);
                }
                join(f,t);
                a2.add(f);
                b2.add(t);
                ejes.add(f*10000+t);
                ejes.add(t*10000+f);
            }
            for(int i=0;i<N;i++)
            for(int j=i+1;j<N;j++)
            if(find(i) != find(j))
            {
                int aa = find(i);
                int bb = find(j);
                ejes.add(aa*10000+bb);
                ejes.add(bb*10000+aa);
                a2.add(aa);
                b2.add(bb);
                join(i,j);
            }
            a = new int[a2.size()];
            b = new int[a2.size()];
            l = new int[a2.size()];
            for(int i=0;i<a2.size();i++)
            {
                a[i] = a2.get(i);
                b[i] = b2.get(i);
                l[i] = r1.nextInt(10000);
            }
        }
        catch (Exception e) { 
            addFatalError("An exception occurred while trying to get your program's results.");
            e.printStackTrace(); 
        }
    }
    public class Eje implements Comparable<Eje> {
        public int peso;
        public int from;
        public int to;
        public Eje(int p, int f, int t)
        {
            peso = p;
            from = f;
            to = t;
        }
        public int compareTo(Eje otro)
        {
            return otro.peso-peso;
        }
    }
    int[] solve()
    {
        ArrayList<Eje> ejes = new ArrayList<>();
        for(int i=0;i<a.length;i++)
        {
            Eje e = new Eje(l[i],a[i],b[i]);
            ejes.add(e);
        }
        Collections.sort(ejes);
        initUF(N);
        int[] res = new int[2];
        res[0] = 0;
        res[1] = 0;
        for(int i=0;i<ejes.size();i++)
        {
            if(find(ejes.get(i).from) != find(ejes.get(i).to))
                join(ejes.get(i).from,ejes.get(i).to);
            else
            {
                res[1] = Math.max(res[1],ejes.get(i).peso);
                res[0] += ejes.get(i).peso;
            }
        }
        return res;
    }
    // -----------------------------------------
    public String runTest(String seed) {
      try {
        generate(seed);

        // call the solution
        int[] ret = camaras(N,a,b,l);

        // check the params of the return
        int sol[] = solve();
        if(ret[0] != sol[0] || ret[1] != sol[1])
            return "Lamentablemente la solución no es correcta :(";
        return "El caso de prueba ha sido resuelto con éxito :)";
      }
      catch (Exception e) { 
        System.err.println("Formato inválido de respuesta.");
        e.printStackTrace(); 
        return "";
      }
    }
// ------------- testing part ------------
    static String exec;
    static Process proc;
    InputStream is;
    OutputStream os;
    BufferedReader br;
    // -----------------------------------------
    int[] camaras(int N, int[] a, int[] b, int[] l) throws IOException {
        try {
            if (proc == null)
                return new int[0];
            //imitate passing params to 'scan'
            StringBuffer sb = new StringBuffer();
            sb.append(N).append(' ').append(a.length).append('\n');
            for (int i=0; i<a.length; i++)
                sb.append(a[i] + " " + b[i] + " " + l[i]).append('\n');
            os.write(sb.toString().getBytes());
            os.flush();

            //imitate receiving return from 'improve'
            BufferedReader br = new BufferedReader(new InputStreamReader(is));
            int[] ret = new int[2];
            String[] st = br.readLine().split(" ");
            ret[0] = Integer.parseInt(st[0]);
            ret[1] = Integer.parseInt(st[1]);
            return ret;
        }
        catch (Exception e) 
        {
            System.err.println("Formato inválido de respuesta.");
            e.printStackTrace(); 
            return new int[0];
        }
    }
    // -----------------------------------------
    public AGMTester(String seed) {
      try {
        //interface for runTest
        if (exec != null) {
            try {
                Runtime rt = Runtime.getRuntime();
                proc = rt.exec(exec);
                os = proc.getOutputStream();
                is = proc.getInputStream();
                br = new BufferedReader(new InputStreamReader(is));
                new ErrorReader(proc.getErrorStream()).start();
            } catch (Exception e) { e.printStackTrace(); }
        }
        System.out.println(runTest(seed));
        if (proc != null)
            try { proc.destroy(); } 
            catch (Exception e) { e.printStackTrace(); }
      }
      catch (Exception e) { e.printStackTrace(); }
    }
    // -----------------------------------------
    public static void main(String[] args) {
        String seed = "1";
        for (int i = 0; i<args.length; i++)
        {   if (args[i].equals("-test"))
                seed = args[++i];
            if (args[i].equals("-exec"))
                exec = args[++i];
        }
        AGMTester f = new AGMTester(seed);
    }
    // -----------------------------------------
    void addFatalError(String message) {
        System.out.println(message);
    }
}

class ErrorReader extends Thread{
    InputStream error;
    public ErrorReader(InputStream is) {
        error = is;
    }
    public void run() {
        try {
            byte[] ch = new byte[50000];
            int read;
            while ((read = error.read(ch)) > 0)
            {   String s = new String(ch,0,read);
                System.out.print(s);
                System.out.flush();
            }
        } catch(Exception e) { }
    }
}
