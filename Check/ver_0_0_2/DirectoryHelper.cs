﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ver_0_0_2
{
    static class DirectoryHelper
    {
        public static void Traverse(this DirectoryInfo info, Action<DirectoryInfo> func) {
            func(info);
            Parallel.ForEach(
                source: info.GetDirectories(),
                body: (dir, state) => {
                    dir.Traverse(func);
                });
        }
    }
}
