# Setup sources
set(IKARUGA_SOURCES
        Actor.cpp
        AnimatedRenderable.cpp
        Bot.cpp
        Camera.cpp
        Collidable.cpp
        Game.cpp
        KillAnimation.cpp
        Level.cpp
        Main.cpp
        MainWindow.cpp
        Player.cpp
        PlayerProperty.cpp
        Renderable.cpp
        SparseMatrix.cpp
        SparseVector.cpp
        StaticRenderable.cpp
        TextureFactory.cpp
        TexturedLayer.cpp
        WorldProperty.cpp
        Weapon.cpp
        Projectile.cpp
        LaserWeapon.cpp
        CollisionManager.cpp
        Armed.cpp
        StatusBar.cpp
        FontRender.cpp
        Sound.cpp
        PowerUp.cpp
        PowerUpHeal.cpp
        HighScore.cpp
        Filesystem.cpp
        Profile.cpp
        MainMenu.cpp
        RenderTable.cpp
        PowerUpWeapon.cpp
        PowerUpGodMode.cpp
        BlasterWeapon.cpp
        RocketWeapon.cpp
        MeatballWeapon.cpp
        CppWeapon.cpp)

set(IKARUGA_LIBS ${IKARUGA_LIBS}
        xml
        ${Boost_LIBRARIES}
        ${SDL2_LIBRARY}
        ${SDL2_IMG_LIBRARY}
        ${SDL2_MIXER_LIBRARY})

# Build executable
add_executable(ikaruga ${IKARUGA_SOURCES})
target_link_libraries(ikaruga ${IKARUGA_LIBS})
